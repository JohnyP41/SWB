.intel_syntax noprefix

.text

.global my_exit

my_exit:
	mov rax, 60
	syscall
	ret


.att_syntax noprefix
