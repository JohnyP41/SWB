//5.1
module SWB (VGA_HS, VGA_VS, VGA_R, VGA_B, VGA_G, CLOCK_27);
wire VGA_CLK;
output reg VGA_HS;
output reg VGA_VS;
output[3:0] VGA_B;
output[3:0] VGA_R;
output[3:0] VGA_G;
input [1:0] CLOCK_27;

integer width;
integer height;

integer top;
integer bottom;
integer left;
integer right;


always
begin
	width = ACTIVE_VIDEO_D;
	height = V_ACTIVE_VIDEO_D;

	top = BACK_PORCH_C + SYNC_PULSE_B;
	bottom = top + height;
	left = V_BACK_PORCH_C + V_SYNC_PULSE_B;
	right = left + width;
end


xdd u0 (
   .clk_in_clk    (CLOCK_27[1]),    //  clk_in.clk
   .clk_res_reset (0), // clk_res.reset
   .clk_out_clk   (VGA_CLK)    // clk_out.clk
);

reg [9:0] HS_count;

//HS signal generator   
always @(posedge VGA_CLK)
begin
  if (HS_count < FRONT_PORCH_A + SYNC_PULSE_B + 
      BACK_PORCH_C + ACTIVE_VIDEO_D)
     HS_count <= HS_count + 1;
  else
     HS_count <= 0;
 
  if (HS_count < SYNC_PULSE_B)
     VGA_HS <= 0;
  else 
     VGA_HS <= 1;
end

reg [9:0] VS_count;
//HS signal generator   
always @(posedge VGA_CLK)
begin
  if (HS_count==0)
  begin
     if (VS_count < V_FRONT_PORCH_A + V_SYNC_PULSE_B 
+ V_BACK_PORCH_C + V_ACTIVE_VIDEO_D)
   VS_count <= VS_count +1;
     else
   VS_count <= 0;
  
     if (VS_count < V_SYNC_PULSE_B)
      VGA_VS <= 0;
     else
      VGA_VS <=1; 
  end
end

assign VGA_B =(HS_count>=BACK_PORCH_C + SYNC_PULSE_B &&
  HS_count <= BACK_PORCH_C + SYNC_PULSE_B + ACTIVE_VIDEO_D &&
  VS_count >= V_BACK_PORCH_C+V_SYNC_PULSE_B && 
  VS_count<= V_BACK_PORCH_C+ V_SYNC_PULSE_B + V_ACTIVE_VIDEO_D) 
     ? 4'd8 : 0;



	  
parameter FRONT_PORCH_A = 16;
parameter SYNC_PULSE_B = 96;
parameter BACK_PORCH_C = 48;
parameter ACTIVE_VIDEO_D = 640;

parameter V_FRONT_PORCH_A = 10;
parameter V_SYNC_PULSE_B = 2;
parameter V_BACK_PORCH_C = 33;
parameter V_ACTIVE_VIDEO_D = 480;

endmodule

//5.2

module p2(VGA_HS, VGA_VS, VGA_R, VGA_B, VGA_G, CLOCK_27);
wire VGA_CLK;
output reg VGA_HS;
output reg VGA_VS;
output[3:0] VGA_B;
output[3:0] VGA_R;
output[3:0] VGA_G;
input [1:0] CLOCK_27;

integer width;
integer height;

integer top;
integer bottom;
integer left;
integer right;

/*
always
begin
	width = ACTIVE_VIDEO_D;
	height = V_ACTIVE_VIDEO_D;

	top = BACK_PORCH_C + SYNC_PULSE_B;
	bottom = top + height;
	left = V_BACK_PORCH_C + V_SYNC_PULSE_B;
	right = left + width;
end
*/

xdd (
   .clk_in_clk    (CLOCK_27[1]),    //  clk_in.clk
   .clk_res_reset (0), // clk_res.reset
   .clk_out_clk   (VGA_CLK)    // clk_out.clk
);

reg [9:0] HS_count;

//HS signal generator   
always @(posedge VGA_CLK)
begin
  if (HS_count < FRONT_PORCH_A + SYNC_PULSE_B + 
      BACK_PORCH_C + ACTIVE_VIDEO_D)
     HS_count <= HS_count + 1;
  else
     HS_count <= 0;
 
  if (HS_count < SYNC_PULSE_B)
     VGA_HS <= 0;
  else 
     VGA_HS <= 1;
end

reg [9:0] VS_count;
//HS signal generator   
always @(posedge VGA_CLK)
begin
  if (HS_count==0)
  begin
     if (VS_count < V_FRONT_PORCH_A + V_SYNC_PULSE_B 
+ V_BACK_PORCH_C + V_ACTIVE_VIDEO_D)
   VS_count <= VS_count +1;
     else
   VS_count <= 0;
  
     if (VS_count < V_SYNC_PULSE_B)
      VGA_VS <= 0;
     else
      VGA_VS <=1; 
  end
end


assign VGA_R =(HS_count >= BACK_PORCH_C + SYNC_PULSE_B &&
               HS_count <= BACK_PORCH_C + SYNC_PULSE_B + ACTIVE_VIDEO_D) &&
               ((VS_count >= V_BACK_PORCH_C+V_SYNC_PULSE_B && 
               VS_count<= V_BACK_PORCH_C+ V_SYNC_PULSE_B + V_ACTIVE_VIDEO_D / 4)
					||( VS_count >= V_BACK_PORCH_C+V_SYNC_PULSE_B + (3*V_ACTIVE_VIDEO_D)/4&& 
				    VS_count<= V_BACK_PORCH_C+ V_SYNC_PULSE_B + V_ACTIVE_VIDEO_D))
     ? 4'd8 : 0;
assign VGA_G =(HS_count >= BACK_PORCH_C + SYNC_PULSE_B &&
               HS_count <= BACK_PORCH_C + SYNC_PULSE_B + ACTIVE_VIDEO_D) &&
               ((VS_count >= V_BACK_PORCH_C+V_SYNC_PULSE_B + V_ACTIVE_VIDEO_D/4&& 
               VS_count<= V_BACK_PORCH_C+ V_SYNC_PULSE_B + V_ACTIVE_VIDEO_D / 2)
					|| ( VS_count >= V_BACK_PORCH_C+V_SYNC_PULSE_B + (3*V_ACTIVE_VIDEO_D)/4&& 
						VS_count<= V_BACK_PORCH_C+ V_SYNC_PULSE_B + V_ACTIVE_VIDEO_D))
					
     ? 4'd8 : 0;
assign VGA_B =(HS_count >= BACK_PORCH_C + SYNC_PULSE_B &&
               HS_count <= BACK_PORCH_C + SYNC_PULSE_B + ACTIVE_VIDEO_D &&
               VS_count >= V_BACK_PORCH_C+V_SYNC_PULSE_B + V_ACTIVE_VIDEO_D/2&& 
               VS_count<= V_BACK_PORCH_C+ V_SYNC_PULSE_B + V_ACTIVE_VIDEO_D)
					
     ? 4'd8 : 0;
	

	  
parameter FRONT_PORCH_A = 16;
parameter SYNC_PULSE_B = 96;
parameter BACK_PORCH_C = 48;
parameter ACTIVE_VIDEO_D = 640;

parameter V_FRONT_PORCH_A = 10;
parameter V_SYNC_PULSE_B = 2;
parameter V_BACK_PORCH_C = 33;
parameter V_ACTIVE_VIDEO_D = 480;

endmodule

//5.3
module SWB (VGA_HS, VGA_VS, VGA_R, VGA_B, VGA_G, CLOCK_27);
wire VGA_CLK;
output reg VGA_HS;
output reg VGA_VS;
output[3:0] VGA_B;
output[3:0] VGA_R;
output[3:0] VGA_G;
input [1:0] CLOCK_27;

integer width;
integer height;

integer top;
integer bottom;
integer left;
integer right;


always
begin
	width = ACTIVE_VIDEO_D;
	height = V_ACTIVE_VIDEO_D;

	top = BACK_PORCH_C + SYNC_PULSE_B;
	bottom = top + height;
	left = V_BACK_PORCH_C + V_SYNC_PULSE_B;
	right = left + width;
end


xdd u0 (
   .clk_in_clk    (CLOCK_27[1]),    //  clk_in.clk
   .clk_res_reset (0), // clk_res.reset
   .clk_out_clk   (VGA_CLK)    // clk_out.clk
);

reg [9:0] HS_count;

//HS signal generator   
always @(posedge VGA_CLK)
begin
  if (HS_count < FRONT_PORCH_A + SYNC_PULSE_B + 
      BACK_PORCH_C + ACTIVE_VIDEO_D)
     HS_count <= HS_count + 1;
  else
     HS_count <= 0;
 
  if (HS_count < SYNC_PULSE_B)
     VGA_HS <= 0;
  else 
     VGA_HS <= 1;
end

reg [9:0] VS_count;
//HS signal generator   
always @(posedge VGA_CLK)
begin
  if (HS_count==0)
  begin
     if (VS_count < V_FRONT_PORCH_A + V_SYNC_PULSE_B 
+ V_BACK_PORCH_C + V_ACTIVE_VIDEO_D)
   VS_count <= VS_count +1;
     else
   VS_count <= 0;
  
     if (VS_count < V_SYNC_PULSE_B)
      VGA_VS <= 0;
     else
      VGA_VS <=1; 
  end
end

// Red on whole
assign VGA_B =(HS_count>=BACK_PORCH_C + SYNC_PULSE_B + ACTIVE_VIDEO_D/3 &&
 HS_count + VS_count <= BACK_PORCH_C + SYNC_PULSE_B + ACTIVE_VIDEO_D*1/2 + V_BACK_PORCH_C+ V_SYNC_PULSE_B + V_ACTIVE_VIDEO_D*2/3 && 
 VS_count >= V_BACK_PORCH_C+V_SYNC_PULSE_B + ACTIVE_VIDEO_D/3
 ) 
     ? 4'd8 : 0;
assign VGA_G =(HS_count>=BACK_PORCH_C + SYNC_PULSE_B + ACTIVE_VIDEO_D/3 &&
 HS_count + VS_count <= BACK_PORCH_C + SYNC_PULSE_B + ACTIVE_VIDEO_D*1/2 + V_BACK_PORCH_C+ V_SYNC_PULSE_B + V_ACTIVE_VIDEO_D*2/3 && 
 VS_count >= V_BACK_PORCH_C+V_SYNC_PULSE_B + ACTIVE_VIDEO_D/3
 ) 
     ? 4'd8 : 0;


	  
parameter FRONT_PORCH_A = 16;
parameter SYNC_PULSE_B = 96;
parameter BACK_PORCH_C = 48;
parameter ACTIVE_VIDEO_D = 640;

parameter V_FRONT_PORCH_A = 10;
parameter V_SYNC_PULSE_B = 2;
parameter V_BACK_PORCH_C = 33;
parameter V_ACTIVE_VIDEO_D = 480;

endmodule

//5.4 - FLAGA ETIOPII

module p2(VGA_HS, VGA_VS, VGA_R, VGA_B, VGA_G, CLOCK_27);
wire VGA_CLK;
output reg VGA_HS;
output reg VGA_VS;
output[3:0] VGA_B;
output[3:0] VGA_R;
output[3:0] VGA_G;
input [1:0] CLOCK_27;

integer width;
integer height;

integer top;
integer bottom;
integer left;
integer right;

/*
always
begin
	width = ACTIVE_VIDEO_D;
	height = V_ACTIVE_VIDEO_D;

	top = BACK_PORCH_C + SYNC_PULSE_B;
	bottom = top + height;
	left = V_BACK_PORCH_C + V_SYNC_PULSE_B;
	right = left + width;
end
*/

xdd (
   .clk_in_clk    (CLOCK_27[1]),    //  clk_in.clk
   .clk_res_reset (0), // clk_res.reset
   .clk_out_clk   (VGA_CLK)    // clk_out.clk
);

reg [9:0] HS_count;

//HS signal generator   
always @(posedge VGA_CLK)
begin
  if (HS_count < FRONT_PORCH_A + SYNC_PULSE_B + 
      BACK_PORCH_C + ACTIVE_VIDEO_D)
     HS_count <= HS_count + 1;
  else
     HS_count <= 0;
 
  if (HS_count < SYNC_PULSE_B)
     VGA_HS <= 0;
  else 
     VGA_HS <= 1;
end

reg [9:0] VS_count;
//HS signal generator   
always @(posedge VGA_CLK)
begin
  if (HS_count==0)
  begin
     if (VS_count < V_FRONT_PORCH_A + V_SYNC_PULSE_B 
+ V_BACK_PORCH_C + V_ACTIVE_VIDEO_D)
   VS_count <= VS_count +1;
     else
   VS_count <= 0;
  
     if (VS_count < V_SYNC_PULSE_B)
      VGA_VS <= 0;
     else
      VGA_VS <=1; 
  end
end

assign VGA_G =(HS_count>=BACK_PORCH_C + SYNC_PULSE_B &&
  HS_count <= BACK_PORCH_C + SYNC_PULSE_B + ACTIVE_VIDEO_D &&
  VS_count >= V_BACK_PORCH_C+V_SYNC_PULSE_B && 
  VS_count<= V_BACK_PORCH_C+ V_SYNC_PULSE_B + (2*V_ACTIVE_VIDEO_D)/3)
     ? 4'd8 : 0;

assign VGA_R =(HS_count>=BACK_PORCH_C + SYNC_PULSE_B &&
  HS_count <= BACK_PORCH_C + SYNC_PULSE_B + ACTIVE_VIDEO_D &&
  VS_count >= V_BACK_PORCH_C+V_SYNC_PULSE_B + V_ACTIVE_VIDEO_D/3 && 
  VS_count<= V_BACK_PORCH_C+ V_SYNC_PULSE_B + V_ACTIVE_VIDEO_D) 
     ? 4'd8 : 0;


	  
parameter FRONT_PORCH_A = 16;
parameter SYNC_PULSE_B = 96;
parameter BACK_PORCH_C = 48;
parameter ACTIVE_VIDEO_D = 640;

parameter V_FRONT_PORCH_A = 10;
parameter V_SYNC_PULSE_B = 2;
parameter V_BACK_PORCH_C = 33;
parameter V_ACTIVE_VIDEO_D = 480;

endmodule