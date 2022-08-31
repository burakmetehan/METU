module PE1 where

import Text.Printf
import Data.List

-- Type synonyms --
type Point = (Double, Double)
type Signal = (Double, Double, Double, Double)

-- This function takes a Double and rounds it to 2 decimal places as requested in the PE --
getRounded :: Double -> Double
getRounded x = read s :: Double
               where s = printf "%.2f" x

-------------------------------------------------------------------------------------------
----------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------

getDistance :: Point -> Point -> Double
getDistance (x1, y1) (x2, y2) = getRounded (sqrt ((x1-x2)^2 + (y1-y2)^2))

-------------------------------------------------------------------------------------------

findAllDistances :: Point -> [Point] -> [Double]
findAllDistances b l = [getRounded(getDistance b n) | n <- l]

-------------------------------------------------------------------------------------------

{-
lower_extreme, higher_extreme
-} 

findExtremes :: Point -> [Point] -> (Point, Point)
findExtremes b l = case l of
    [] -> ((-1, -1), (-1, -1)) -- Error: Instead use => [] -> (x, x)
    _ -> let value = findExtremes b (tail l) in
        if getDistance b (head l) <= getDistance b (fst value) then (head l, snd value)
        else if getDistance b (head l) >= getDistance b (snd value) then (fst value, head l)
        else value

-------------------------------------------------------------------------------------------

getnth :: Signal -> Int -> Double
getnth (a, b, c, d) n = case n of
    0 -> a
    1 -> b
    2 -> c
    3 -> d
    _ -> 0

northSouth :: Signal -> String
northSouth signal 
    | res > 0 = "North"
    | res == 0 = ""
    | res < 0 = "South"
    | otherwise = ""
    where res = getnth signal 0 - getnth signal 2

westEast :: Signal -> String 
westEast signal 
    | res > 0 = "West"
    | res == 0 = ""
    | res < 0 = "East"
    | otherwise = ""
    where res = getnth signal 3 - getnth signal 1

getSingleAction :: Signal -> String
getSingleAction signal = 
    if str /= "" then str
    else "Stay"
    where str = northSouth signal ++ westEast signal

-------------------------------------------------------------------------------------------

getAllActions :: [Signal] -> [String]
getAllActions signals = [getSingleAction signal | signal <- signals]

-------------------------------------------------------------------------------------------

numberOfGivenAction :: Num a => [Signal] -> String -> a
numberOfGivenAction signals action = fromIntegral $length[signal | signal <- signals, getSingleAction signal == action]