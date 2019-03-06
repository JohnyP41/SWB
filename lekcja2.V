---zad2.1---

module zad1 (SW, KEY, LEDR, HEX0, HEX1, HEX2, HEX3);
input [9:0] SW;
input [3:0] KEY;
output reg [9:0] LEDR;
output[6:0] HEX0;
output[6:0] HEX1;
output[6:0] HEX2;
output[6:0] HEX3;


always
if(KEY[0] == 0)
	LEDR[9:0] = SW[9:5] + SW[4:0];
else if(KEY[1] == 0)
	LEDR[9:0] = SW[9:5] - SW[4:0];
else if(KEY[2] == 0)
	LEDR[9:0] = SW[9:5] * SW[4:0];
else
	LEDR[9:0] = SW[9:0];
endmodule

---zad2.2---

module SWB (SW, KEY, LEDR, HEX0, HEX1, HEX2, HEX3);
input [9:0] SW;
input [3:0] KEY;
output reg [9:0] LEDR;
output [6:0] HEX0;
output [6:0] HEX1;
output [6:0] HEX2;
output [6:0] HEX3;


dec_to_hex y0 (LEDR[9:0] % 10, HEX0);
dec_to_hex y1 ((LEDR[9:0] / 10) %10 , HEX1);
dec_to_hex y2 ((LEDR[9:0] / 100) %10, HEX2);
dec_to_hex y3 ((LEDR[9:0] / 1000) %10, HEX3);

always
if(KEY[0] == 0)
	LEDR[9:0] = SW[9:5] + SW[4:0];
else if(KEY[1] == 0)
	LEDR[9:0] = SW[9:5] - SW[4:0];
else if(KEY[2] == 0)
	LEDR[9:0] = SW[9:5] * SW[4:0];
else
	LEDR[9:0] = SW[9:0];
	
endmodule

module dec_to_hex(dec, hex);
input [3:0] dec;
output reg [6:0] hex;

always
case (dec)
	0: hex = 7'b1000000;
	1: hex = 7'b1111001;
	2: hex = 7'b0100100;
	3: hex = 7'b0110000;
	4: hex = 7'b0110001;
	5: hex = 7'b0010010;
 	6: hex = 7'b0000010;
	7: hex = 7'b1111000;
	8: hex = 7'b0000000;
	9: hex = 7'b0011000;
	default: hex = 7'b1111111;
endcase
endmodule

---zad1.1 part 3---

module zad1 (SW, KEY, LEDR, HEX0, HEX1, HEX2, HEX3);
input [9:0] SW;
input [3:0] KEY;
output reg [9:0] LEDR;
output [6:0] HEX0;
output [6:0] HEX1;
output [6:0] HEX2;
output [6:0] HEX3;


dec_to_hex y0 (LEDR[8:0] % 10, HEX0);
dec_to_hex y1 ((LEDR[8:0] / 10) %10 , HEX1);
dec_to_hex y2 ((LEDR[8:0] / 100) %10, HEX2);
//dec_to_hex y3 ((LEDR[9:0] / 1000) %10, HEX3);
dec_to_hex y3 (LEDR[9] * 10, HEX3);


always
if(KEY[0] == 0)
	begin
	LEDR[9] = 0;
	LEDR[8:0] = SW[9:5] + SW[4:0];
	end
else if(KEY[1] == 0)
	begin
	if (SW[9:5] < SW[4:0])
		begin
		LEDR[9] = 1;
		LEDR[8:0] = SW[4:0] - SW[9:5];
	   end
	else
		begin
		LEDR[9] = 0;
		LEDR[8:0] = SW[9:5] - SW[4:0];
		end
	end
else if(KEY[2] == 0)
	begin
	LEDR[9] = 0;
	LEDR[8:0] = SW[9:5] * SW[4:0];
	end
else
	begin
	LEDR[9] = 0;
	LEDR[8:0] = SW[9:0];
	end
	
endmodule

module dec_to_hex(dec, hex);
input [3:0] dec;
output reg [6:0] hex;

always
case (dec)
	10: hex = 7'b0111111;
	0: hex = 7'b1000000;
	1: hex = 7'b1111001;
	2: hex = 7'b0100100;
	3: hex = 7'b0110000;
	4: hex = 7'b0110001;
	5: hex = 7'b0010010;
 	6: hex = 7'b0000010;
	7: hex = 7'b1111000;
	8: hex = 7'b0000000;
	9: hex = 7'b0011000;
	default: hex = 7'b1111111;
endcase
endmodule

