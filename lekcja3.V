---Zadanie Z3.1 (1 p.)---
module zad1 (clk,SW,KEY,LEDR,HEX0,HEX1,HEX2,HEX3,dec,hex,hex1,hex2);

	input clk;
	input[9:0] SW;
	input[2:0] KEY;
	output[8:0] LEDR;
	output reg[8:0] hex;
	output reg[8:0] hex1;
	output reg[8:0] hex2;
	output[6:0] HEX3;
	output[6:0] HEX2;
	output[6:0] HEX1;
	output[6:0] HEX0;
	output reg[0:8] dec;
	initial
	begin
	hex1 = 0;
	hex2 = 0;
	end
	
	always @ (posedge clk)
	begin
	if(!KEY[0])
		begin
		hex[8:0] = SW[4:0] + SW[9:5];
		hex1 = hex/100;
		hex2 = hex%100;
		end
	else if(!KEY[1])
		begin
			hex[8:0] = SW[9:5] - SW[4:0];
			if(SW[9:5] < SW[4:0])
				begin
					hex1 = 100;
					hex = SW[4:0] - SW[9:5];
					hex2 = hex%100;
				end
			else
				begin
					hex1 = hex/100;
					hex2 = hex%100;
				end
		end
	else if(!KEY[2])
	begin
		hex[8:0] = SW[4:0] * SW[9:5];
		hex1 = hex/100;
		hex2 = hex%100;
		end
	/*else
		begin
			if(SW[9:5] > 0)
					begin
					hex1 = SW[9:5];
					end
				else if(SW[9:5] == 0)
					hex1 = 0;
				if(SW[4:0] > 0)
					begin
					hex2 = SW[4:0];
					end
				else if(SW[4:0] == 0)
					hex2 = 0;
		end*/
	end
	p22(hex1/10,HEX3);
	p22(hex1%10,HEX2);
	p22(hex2/10,HEX1);
	p22(hex2%10,HEX0);	
endmodule	

module p22(dec, hex);
		input [8:0] dec;
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
