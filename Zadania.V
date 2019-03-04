//Czesc 1
//Przycisk KEY0 jest w stanie 0 gdy jest nacisniety.
//Dioda LED0 jest w stanie 1 jest zapalona.

//Czesc 2
module SWB (KEY, LEDG);
input[1:0] KEY;
output[0:0] LEDG;

assign LEDG[0] = !KEY[0] & !KEY[1];

endmodule

//Czesc 3

module SWB (KEY, LEDG);
input[1:0] KEY;
output[0:0] LEDG;

assign LEDG[0] = !KEY[0] | !KEY[1];

endmodule

//Zadanie 2

module SWB (KEY, LEDG);
input[3:0] KEY;
output[7:0] LEDG;

assign LEDG[7:0] = !KEY[0]+!KEY[1]+!KEY[2]+!KEY[3];

endmodule



module SWB (KEY, LEDG,SW,LEDR,HEX0,HEX1,HEX2,HEX3);
input[3:0] KEY;
input[9:0] SW;
output[7:0] LEDG;
output[9:0] LEDR;
output[6:0] HEX0;
output[6:0] HEX1;
output[6:0] HEX2;
output[6:0] HEX3;



assign LEDG[7:0] = !KEY[0]+!KEY[1]+!KEY[2]+!KEY[3];
assign LEDR[9:0] = SW[9:0];
assign HEX0[6:0] = 7'b0000000;
assign HEX1[6:0] = 7'b0100100;
assign HEX2[6:0] = 7'b0100100;
assign HEX3[6:0] = 7'b0000010;

endmodule

module SWB (KEY, LEDG,SW,LEDR,HEX0,HEX1,HEX2,HEX3);
input[3:0] KEY;
input[9:0] SW;
output[7:0] LEDG;
output[9:0] LEDR;
output[6:0] HEX0;
output[6:0] HEX1;
output[6:0] HEX2;
output[6:0] HEX3;



assign LEDG[7:0] = !KEY[0]+!KEY[1]+!KEY[2]+!KEY[3];
assign LEDR[9:0] = SW[9:0];
assign HEX0[6:0] = 7'b0000000;
assign HEX1[6:0] = 7'b0100100;
assign HEX2[6:0] = 7'b0100100;
assign HEX3[6:0] = 7'b0000010;

endmodule




module SWB (HEX0,HEX1,HEX2,HEX3);
output[6:0] HEX0;
output[6:0] HEX1;
output[6:0] HEX2;
output[6:0] HEX3;

endmodule

module dec_to_hex(dec, hex);
input [3:0] dec;
output [6:0] hex;

case (dec)
	0: 7'b1000000;
	2: 7'b0100100;
	6: 7'b0000000;
	8: 7'b0000010;
endmodule;


module SWB (SW, HEX0,HEX1,HEX2,HEX3);
input [3:0] SW;
output[6:0] HEX0;
output[6:0] HEX1;
output[6:0] HEX2;
output[6:0] HEX3;

dec_to_hex(8,HEX0);
dec_to_hex(2,HEX1);
dec_to_hex(2,HEX2);
dec_to_hex(6,HEX3);


endmodule

module dec_to_hex(dec, hex);
input [3:0] dec;
output reg [6:0] hex;

always
case (dec)
	0: hex = 7'b1000000;
	1: hex = 7'b1111001;
	2: hex = 7'b0100100;
	3: hex = 7'b1011000;
	4: hex = 7'b1001100;
	5: hex = 7'b1001000;
 	6: hex = 7'b0000010;
	7: hex = 7'b1111000;
	8: hex = 7'b0000000;
	9: hex = 7'b1111000;
	default: hex = 7'b1111111;
endcase
endmodule

//Zadanie 2.1
module SWB (SW, KEY, LEDR, HEX0, HEX1, HEX2, HEX3);
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

//#zadanie 2.2
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