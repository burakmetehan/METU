`timescale 1ns / 1ps 
module lab3_2(
      input[4:0] smartCode,
      input CLK, 
      input lab, //0:Digital, 1:Mera
      input [1:0] mode, //00:exit, 01:enter, 1x: idle 
      output reg [5:0] numOfStuInMera,
      output reg [5:0] numOfStuInDigital,
      output reg restrictionWarnMera,//1:show warning, 0:do not show warning
      output reg isFullMera, //1:full, 0:not full
      output reg isEmptyMera, //1: empty, 0:not empty
      output reg unlockMera,	//1:door is open, 0:closed
      output reg restrictionWarnDigital,//1:show warning, 0:do not show warning
      output reg isFullDigital, //1:full, 0:not full
      output reg isEmptyDigital, //1: empty, 0:not empty
      output reg unlockDigital //1:door is open, 0:closed
  );

  // You may declare your variables below	
  reg[2:0] number_of_one;
  initial begin
    numOfStuInMera=0;
    numOfStuInDigital=0;
    restrictionWarnMera=0;
    isFullMera=0;
    isEmptyMera=1'b1;
    unlockMera=0;		
    restrictionWarnDigital=0;
    isFullDigital=0;
    isEmptyDigital=1'b1;
    unlockDigital=0;
    number_of_one = 0;
  end
  //Modify the lines below to implement your design
  always @(posedge CLK)
  begin
    restrictionWarnDigital = 0;
    restrictionWarnMera = 0;
    unlockDigital = 0;
    unlockMera = 0;

    if (mode == 2'b00) begin // Exit
      if (lab == 0) begin // Lab: Digital
        if (isEmptyDigital == 0) begin // lab is not empty
          unlockDigital = 1'b1;
          numOfStuInDigital = numOfStuInDigital - 6'd1;
          isFullDigital = 0;
          if (numOfStuInDigital == 0) begin // lab is now empty
            isEmptyDigital = 1'b1;
          end
        end
        else begin // lab is empty and exit, Error
          unlockDigital = 0;
        end
      end
      else begin // Lab: Mera
        if (isEmptyMera == 0) begin // lab is not empty
            unlockMera = 1'b1;
            numOfStuInMera = numOfStuInMera - 6'd1;
            isFullMera = 0;
            if (numOfStuInMera == 0) begin // lab is now empty
              isEmptyMera = 1'b1;
            end
          end
          else begin // lab is empty and exit, Error
            unlockMera = 0;
          end
      end
    end
    else if (mode == 2'b01) begin // Entry
      if (lab == 0) begin // Lab: Digital
        if (isFullDigital == 1) begin // lab is full
          unlockDigital = 0; // No need but, just in case
        end
        else begin // lab is not full
          // Number of Student Check
          if (numOfStuInDigital < 15) begin // do not check card code, can enter
            unlockDigital = 1'b1;
            numOfStuInDigital = numOfStuInDigital + 6'd1;
            isEmptyDigital = 0;
          end 
          else begin // numOfStuInDigital >= 15, check card code
            // Smart Code Check
            number_of_one = smartCode[0] + smartCode[1] + smartCode[2] + smartCode[3] + smartCode[4];
            if (number_of_one % 2 == 1) begin // odd number of 1, can enter
              unlockDigital = 1'b1;
              numOfStuInDigital = numOfStuInDigital + 6'd1;
              if(numOfStuInDigital == 30) begin // checking whether lab is ful or not
                isFullDigital = 1'b1;
              end
            end
            else begin // even number of 1, cannot enter
              unlockDigital = 0; // No need, but just in case
              restrictionWarnDigital = 1'b1;
            end
          end
        end
      end 
      else begin // Lab: Mera
        if (isFullMera == 1) begin // lab is full
          unlockMera = 0; // No need, but just in case
        end
        else begin // lab is not full
          // Number of Student Check
          if (numOfStuInMera < 15) begin // do not check card code, can enter
            unlockMera = 1'b1;
            numOfStuInMera = numOfStuInMera + 6'd1;
            isEmptyMera = 0;
          end
          else begin // numOfStuInMera >= 15, check card code
            // Smart Code Check
            number_of_one = smartCode[0] + smartCode[1] + smartCode[2] + smartCode[3] + smartCode[4];
            if (number_of_one % 2 == 0) begin // even number of 1, can enter
              unlockMera = 1'b1;
              numOfStuInMera = numOfStuInMera + 6'd1;
              if (numOfStuInMera == 30) begin // checking whether lab is full or not
                isFullMera = 1;
              end
            end
            else begin // odd number of 1, cannot enter
              unlockMera = 0; // No need, but just in case
              restrictionWarnMera = 1'b1;
            end
          end
        end  
      end
    end
    else; // Idle, default staff is done in the start of the execution. No need to do anything
  end
endmodule
