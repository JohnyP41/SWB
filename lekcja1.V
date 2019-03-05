---test---

module zad1 (KEY, LEDR);
input[0:0] KEY;
output[0:0] LEDR;

assign LEDR[0] = 1;

endmodule

---zad1.1 part 2---

module zad1 (KEY, LEDR);
input[0:1] KEY;
output[0:0] LEDR;

assign LEDR[0] = KEY[0] | KEY[1];

endmodule

---zad1.1 part 3---

module zad1 (KEY, LEDR);
input[0:1] KEY;
output[0:0] LEDR;

assign LEDR[0] = ~(KEY[0] & KEY[1]);

endmodule

---zad1.2 part 1---

module zad1 (KEY, LEDR);
input[0:3] KEY;
output[6:4] LEDR;

assign LEDR[6:4] = !KEY[0] + !KEY[1] + !KEY[2] + !KEY[3];

endmodule

---zad1.2 part 2---

module zad1 (SW, LEDR);
input[8:9] SW;
output[8:9] LEDR;

assign LEDR[8:9] = SW[8:9];

endmodule

---zad1.3---

module zad1 (HEX0, HEX1, HEX2, HEX3);
output[0:6] HEX0;
output[0:6] HEX1;
output[0:6] HEX2;
output[0:6] HEX3;
//6256

assign HEX0[1] = 1;

assign HEX1[1] = 1;
assign HEX1[4] = 1;

assign HEX2[2] = 1;
assign HEX2[5] = 1;

assign HEX3[1] = 1;

endmodule

---zadD1.1---

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

---zadD1.2---

module zad1 (SW, HEX0,HEX1,HEX2,HEX3);
input [3:0] SW;
output[6:0] HEX0;
output[6:0] HEX1;
output[6:0] HEX2;
output[6:0] HEX3;

dec_to_hex(6,HEX0);
dec_to_hex(2,HEX1);
dec_to_hex(5,HEX2);
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




