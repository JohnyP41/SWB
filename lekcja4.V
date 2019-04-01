//Zadanie 4.1 werjsa 1

module p2(KEY,HEX0,HEX1,HEX2,HEX3,a , b , hex);
	input[0:0] KEY;
	output[6:0] HEX0;
	output[6:0] HEX1;
	output[6:0] HEX2;
	output[6:0] HEX3;
	output reg [13:0] a;
	output reg [13:0] b;
	output reg [13:0] hex;
	initial
	begin
		hex = 0;
		a = 0;
		b = 0;
	end
	always		
	begin
	if(!KEY[0])
	begin
		b = (11*a + 7)%10;
		a = b;
	end
	else
	begin
		hex = b;
	end
	end
		p22(hex,HEX0);
		p22(100,HEX1);
		p22(100,HEX2);
		p22(100,HEX3);
endmodule

module p22(dec, hex);
		input [13:0] dec;
		output reg [6:0] hex;
		always
		case (dec)
			0: hex = 7'b1000000;
			1: hex = 7'b1111001;
			2: hex = 7'b0100100;
			3: hex = 7'b0110000;
			4: hex = 7'b0011001;
			5: hex = 7'b0010010;
			6: hex = 7'b0000010;
			7: hex = 7'b1111000;
			8: hex = 7'b0000000;
			9: hex = 7'b0010000;
			100: hex = 7'b1111111;
			default: hex = 7'b1000000;
		endcase
endmodule

//Zadanie 4.1 wersja 2

module p2(CLOCK_50,KEY,HEX0,HEX1,HEX2,HEX3,a,hex);
	input[0:0] KEY;
	input CLOCK_50;
	output[6:0] HEX0;
	output[6:0] HEX1;
	output[6:0] HEX2;
	output[6:0] HEX3;
	output reg [3:0] a;
	output reg [13:0] hex;
	initial
	begin
		hex = 0;
		a = 0;
	end
	always @(posedge CLOCK_50)	
	begin
	if(!KEY[0])
	begin
	a = (a+1)%10;
	end
	else
	begin
		hex = a;
	end
	end
		p22(hex,HEX0);
		p22(100,HEX1);
		p22(100,HEX2);
		p22(100,HEX3);
endmodule

module p22(dec, hex);
		input [13:0] dec;
		output reg [6:0] hex;
		always
		case (dec)
			0: hex = 7'b1000000;
			1: hex = 7'b1111001;
			2: hex = 7'b0100100;
			3: hex = 7'b0110000;
			4: hex = 7'b0011001;
			5: hex = 7'b0010010;
			6: hex = 7'b0000010;
			7: hex = 7'b1111000;
			8: hex = 7'b0000000;
			9: hex = 7'b0010000;
			100: hex = 7'b1111111;
			default: hex = 7'b1000000;
		endcase
endmodule

//Zadanie 4.2

module p2(CLOCK_50,LEDR,KEY,HEX0,HEX1,HEX2,HEX3, b,a , hex, LEDG,SW,c,h,bool,R, set, counter,RO );
	input CLOCK_50;	
	input[3:0] KEY;
	input[9:9] SW;
	output[9:0] LEDR;
	output[7:0] LEDG;
	output[6:0] HEX0;
	output[6:0] HEX1;
	output[6:0] HEX2;
	output[6:0] HEX3;
	output reg [25:0] R;
	output reg [25:0] RO;
	output reg [13:0] c;
	output reg [13:0] b;
	output reg [25:0] a;
	output reg [13:0] hex;
	output reg [1:0] bool;
	output reg [14:0] counter;
	output reg [1:0] h;
	output reg [1:0] set;
	
	initial
	begin
		hex = 0;
		bool = 0;
		h = 0;
		b = 0;
		a = 0;
		set = 0;
	end
	assign LEDR = 0;
	always @(posedge CLOCK_50)
	begin
		if(SW[9] && set == 0)
		 bool = 1;
		if(!SW[9])
		begin
			bool = 0;
			set = 0;
			h = 0;
			hex = 0;
			R = 0;
		end
		if(bool == 1)
		begin
			if (R < 75000000 - a)
				R = R + 1;
			else
			begin
				R = 0;
				c = c + 1;
				bool = 0;
			end
			if(c == 1)
			begin
				c = 0;
				h = 1; 
			end
		end
		if(h == 1)
		begin
			if(b <= 32 & hex >=0)
				hex = 2;
			else if (b <= 64)
				hex = 8;
			else if (b <= 96)
				hex = 32;
			else
				hex = 128;
			h = 0;
			set = 1;
		end
		if(set == 1)
		begin
			if (RO < 5000000)
				RO = RO + 1;
			else
			begin
				RO = 0;
					counter = (counter + 1)%10000;
			end
			if(hex == 2)
			begin
				if(!KEY[0] && KEY[1] && KEY[2] && KEY[3])
				begin
					set = 0;
					hex = 0;
				end
			end
			else if(hex == 8)
			begin
				if(!KEY[1] && KEY[0] && KEY[2] && KEY[3])
				begin
					set = 0;
					hex = 0;
				end
			end
			else if(hex == 32)
			begin
				if(!KEY[2] && KEY[0] && KEY[1] && KEY[3])
				begin
					set = 0;
					hex = 0;
				end
			end
			else
			begin
				if(!KEY[3] && KEY[0] && KEY[1] && KEY[2])
				begin
					set = 0;
					hex = 0;
				end
			end
		end
		b = (b+1)%129;
		a = (a+1)%50000000;
	end
		assign LEDG = hex;
		p22(counter%10,HEX0);
		p22((counter/10)%10,HEX1);
		p22((counter/100)%10,HEX2);
		p22(counter/1000,HEX3);
endmodule

module p22(dec, hex);
		input [14:0] dec;
		output reg [6:0] hex;
		always
		case (dec)
			0: hex = 7'b1000000;
			1: hex = 7'b1111001;
			2: hex = 7'b0100100;
			3: hex = 7'b0110000;
			4: hex = 7'b0011001;
			5: hex = 7'b0010010;
			6: hex = 7'b0000010;
			7: hex = 7'b1111000;
			8: hex = 7'b0000000;
			9: hex = 7'b0010000;
			10: hex = 7'b0111111;
			11: hex = 7'b1111111;
			default: hex = 7'b1111111;
		endcase
endmodule
