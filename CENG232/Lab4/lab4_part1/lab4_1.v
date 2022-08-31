`timescale 1ns / 1ps
module lab4ROM (input [3:0] romAddr, output reg[4:0] romOutput);

	/*Write your code here*/
	always @(*) begin
		case (romAddr)
			4'b0000: romOutput = 5'b00000;
			4'b0001: romOutput = 5'b00001;
			4'b0010: romOutput = 5'b00110;
			4'b0011: romOutput = 5'b00111;
			4'b0100: romOutput = 5'b01011;
			4'b0101: romOutput = 5'b01100;
			4'b0110: romOutput = 5'b01101;
			4'b0111: romOutput = 5'b01110;
			4'b1000: romOutput = 5'b11101;
			4'b1001: romOutput = 5'b11110;
			4'b1010: romOutput = 5'b11111;
			4'b1011: romOutput = 5'b10000;
			4'b1100: romOutput = 5'b10111;
			4'b1101: romOutput = 5'b11000;
			4'b1110: romOutput = 5'b11001;
			4'b1111: romOutput = 5'b11010;
		endcase
	end

endmodule

module lab4RAM (
	input ramMode, //0:read, 1:write
	input [3:0] ramAddr, 
	input [4:0] ramInput,
	input  ramOp, //0:polynomial, 1:derivative
	input [1:0] ramArg,  //00:+1, 01:+2, 10:-1, 11:-2
	input CLK, 
	output reg [8:0] ramOutput);

	/*Write your code here*/
	reg [8:0] ram [15:0];
	integer i, res, arg;

	initial begin
		ramOutput = 9'd0;
		for (i = 0; i < 16; i = i + 1) begin
			ram[i] = 9'd0;
		end

		i = 0;
		res = 0;
		arg = 0;
	end

	always @(*) begin
		if (ramMode == 0) begin // Read
			ramOutput = ram[ramAddr];
		end
	end

	always @(posedge CLK) begin
		res = 0;
		
		if (ramMode == 1) begin // Write
			case (ramArg)
				2'b00: arg = 1;
				2'b01: arg = 2;
				2'b10: arg = -1;
				2'b11: arg = -2;
			endcase

			if (ramOp == 0) begin // polynomial
				for (i = 0; i < 5; i = i + 1) begin
					if (ramInput[4-i] == 0) begin
						res = res + arg ** (4-i);
					end else begin
						res = res - arg ** (4-i);				
					end
				end
			end else begin // derivative
				for (i = 0; i < 4; i = i + 1) begin
					if (ramInput[4-i] == 0) begin
						res = res + (4-i) * (arg ** (3-i));
					end else begin
						res = res - (4-i) * (arg ** (3-i));				
					end
				end
			end

			if (res < 0) begin
				res = res * (-1);
				ram[ramAddr][8] = 1;
			end else begin
				ram[ramAddr][8] = 0;
			end
	
			ram[ramAddr][7:0] = res[7:0];
		end
	end

endmodule


module polMEM(input mode, input [3:0] memAddr, input op, input [1:0] arg, input CLK, output wire [8:0] memOutput);

	/*Don't edit this module*/
	wire [4:0]  romOutput;

	lab4ROM RO(memAddr, romOutput);
	lab4RAM RA(mode, memAddr, romOutput, op, arg, CLK, memOutput);



endmodule
