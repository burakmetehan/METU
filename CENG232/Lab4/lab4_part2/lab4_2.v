`timescale 1ns / 1ps

module lab4_2(// INPUTS
              input wire      mode,
              input wire[2:0] opCode,
              input wire[3:0] value,
              input clk,
              input reset,
              // OUTPUTS
              output reg[9:0] result,
              output reg cacheFull,
              output reg invalidOp,
              output reg overflow);

  //================//
  // INITIAL BLOCK  //
  //================//
  //Modify the lines below to implement your design
  integer i, j, next_loop_i, op_num;
  reg [2:0] op_codes [0:31];
  reg [3:0] values [0:31];
  reg [9:0] p0;
  reg [9:0] p1;
  reg [10:0] overflow_check;

  initial begin
    /* My Variables */
    op_num = 0;
    next_loop_i = 0;
    p0 = 0;
    p1 = 0;
    i = 0;
    j = 0;

    /* Output Variables */
    result = 0;
    cacheFull = 0;
    invalidOp = 0;
    overflow = 0;
  end

  always @(posedge reset or posedge clk) begin
    if (reset) begin // Reset Signal
      op_num = 0;
      next_loop_i = 0;
      p0 = 0;
      p1 = 0;
      result = 0;
      cacheFull = 0;
      invalidOp = 0;
      overflow = 0;

      i = 0;
      j = 0;
    end else begin // clk Signal
      cacheFull = 0;
      invalidOp = 0;

      if (i >= op_num) begin
        i = next_loop_i;
      end

      if (mode == 0) begin // Load
        if (opCode == 3'b111) begin // Invalid opCode
          invalidOp = 1'b1;
          if (op_num >= 32) begin
            cacheFull = 1;
          end
        end else if (opCode == 3'b011) begin // Invalid opCode
          invalidOp = 1'b1;
          if (op_num >= 32) begin
            cacheFull = 1;
          end
        end else begin // Valid opCode
          if (op_num >= 32) begin
            cacheFull = 1'b1;
          end else begin
            op_codes[op_num][2:0] = opCode[2:0];
            values[op_num][3:0] = value[3:0];
            op_num = op_num + 1;
          end
        end
      end else begin
        p1 = p0;
        p0 = result;
        overflow = 0;

        if (op_codes[i][2:0] == 3'b000) begin
          result = p0 + {6'b000000, values[i]};
          overflow_check = {7'b000000, values[i]} + {1'b0, p0};
          if (overflow_check > 11'b01111111111) begin
            overflow = 1;
          end
        end else if (op_codes[i][2:0] == 3'b001) begin
          result = p0 + p1 + {6'b000000, values[i]};
          overflow_check = {7'b000000, values[i]} + {1'b0, p0} + {1'b0, p1};
          if (overflow_check > 11'b01111111111) begin
            overflow = 1;
          end
        end else if (op_codes[i][2:0] == 3'b010) begin
          result = p0 * p1 + {6'b000000, values[i]};
          overflow_check = {7'b000000, values[i]} + {1'b0, p0} * {1'b0, p1};
          if (overflow_check > 11'b01111111111) begin
            overflow = 1;
          end
        end else if (op_codes[i][2:0] == 3'b011) begin // invalid
          result = result;
        end else if (op_codes[i][2:0] == 3'b100) begin
          result = p0[9] + p0[8] + p0[7] + p0[6] + p0[5] + p0[4] + p0[3] + p0[2] + p0[1] + p0[0];
        end else if (op_codes[i][2:0] == 3'b101) begin
            for (j = 9; j >= 0; j = j - 1) begin
              result[9-j] = p0[j];
            end
        end else if (op_codes[i][2:0] == 3'b110) begin
          next_loop_i = {28'b000000, values[i]};
          result = result;
        end else begin // invalid
          result = result;
        end

        i = i + 1;
      end
    end    
  end
endmodule
