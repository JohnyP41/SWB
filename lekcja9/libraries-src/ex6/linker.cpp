#include <cstdio>
#include <sys/stat.h> /* for chmod */

#include "ElfRelocObject.h"
#include "ElfExecutable.h"
#include "Section.h"
#include "Symbol.h"
#include "Debug.h"


int main(int argc, char * argv[])
{
	if (argc < 3)
	{
		puts("No input files or no output file name.");
		return 0;
	}
	ElfExecutable elfExecutable;
	for (int i = 1; i < argc - 1; ++i)
	{
		char * fname = argv[i];
		printf("Processing file %s...\n", fname);
		FILE * f = fopen(fname, "r");
		if (! f)
		{
			printf("Failed to open file %s.\n", fname);
			return 1;
		}
		ElfRelocObject o(i);
		o.Load(f);
		fclose(f);
		elfExecutable.Add(&o);
	}
	puts("Reading input files done. Generating an executable ELF file...");
	elfExecutable.Layout();
	elfExecutable.ProcessRelocations();
	FILE * out = fopen(argv[argc-1], "w");
	if (! out)
	{
		printf("Failed to open file %s for writing.", argv[argc-1]);
		return 1;
	}
	elfExecutable.Write(out);
	fclose(out);
	chmod(argv[argc-1], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	return 0;
}
