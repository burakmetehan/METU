{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use head" #-}
{-# HLINT ignore "Use :" #-}
{-# HLINT ignore "Use bimap" #-}
module PE3 where

-- can use these if you want to...
import Data.List
import Data.Maybe
import Distribution.Simple.Program.HcPkg (list)
import Text.XHtml (HTMLTABLE(cell))

data Private = Private { idNumber :: Int, height :: Int, timeToSwap :: Int } deriving Show

data Cell = Empty | Full Private deriving Show

type Area = [[Cell]]

---------------------------------------------------------------------------------------------
------------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
--------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
--------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
---------------------------------------------------------------------------------------------


-- Note: undefined is a value that causes an error when evaluated. Replace it with
-- a viable definition! Name your arguments as you like by changing the holes: _

--------------------------
-- Part I: Warming up with Abstractions

-- bubbleHumans: Applying a parallel bubble step on integers.
bubbleHumans :: [Int] -> [Int]
bubbleHumans list
    | null first_two = []
    | length first_two == 1 = list
    | first_two !! 0 < first_two !! 1 = [first_two !! 1, first_two !! 0] ++ bubbleHumans (snd splited_list)
    | otherwise = [first_two !! 0] ++ bubbleHumans (tail list)
    where splited_list = splitAt 2 list; first_two = fst splited_list

-- bubblePrivates: The same thing, but on privates with a key function and an asc/desc option.

-- Ascending Helper
ascHelper ::(Private -> Int) -> [Private] -> [Private]
ascHelper func list
    | null first_two = []
    | length first_two == 1 = list
    | func (first_two !! 0) > func (first_two !! 1) = [first_two !! 1, first_two !! 0] ++ ascHelper func (snd splited_list)
    | otherwise = [first_two !! 0] ++ ascHelper func (tail list)
    where splited_list = splitAt 2 list; first_two = fst splited_list

-- Descending Helper
desHelper :: (Private -> Int) -> [Private] -> [Private]
desHelper func list
    | null first_two = []
    | length first_two == 1 = list
    | func (first_two !! 0) < func (first_two !! 1) = [first_two !! 1, first_two !! 0] ++ desHelper func (snd splited_list)
    | otherwise = [first_two !! 0] ++ desHelper func (tail list)
    where splited_list = splitAt 2 list; first_two = fst splited_list

bubblePrivates :: (Private -> Int) -> Bool -> [Private] -> [Private]
bubblePrivates func asc list =
    if asc then desHelper func list
    else ascHelper func list

-- sortPrivatesByHeight: Full sort via multiple bubble steps, calculate the sorting time too!

--Running n times helper
allSortHelper :: Int -> [Private] -> ([Private], Int)
allSortHelper slowest list
    | null first_two = ([], slowest)
    | length first_two == 1 = (list, slowest)
    | height (first_two !! 0) < height (first_two !! 1) = let
                                                            temp_last = allSortHelper 0 (snd splited_list);
                                                            cost = max (timeToSwap (first_two !! 0)) (timeToSwap (first_two !! 1)) in
                                                                (
                                                                    [first_two !! 1, first_two !! 0] ++ fst temp_last,
                                                                    max (max slowest cost) (snd temp_last)
                                                                )
    | otherwise = let temp_tail = allSortHelper 0 (tail list) in
                    (
                        [first_two !! 0] ++ fst temp_tail,
                        max slowest (snd temp_tail)
                    )
    where splited_list = splitAt 2 list; first_two = fst splited_list

runNTimesAllSort :: Int -> Int -> [Private] -> ([Private], Int)
runNTimesAllSort n total list
    | n <= 0 = (list, total)
    | otherwise = runNTimesAllSort (n-1) (total + snd one_run) (fst one_run) --n > 0
    where one_run = allSortHelper 0 list --0 is slowest


sortPrivatesByHeight :: [Private] -> ([Private], Int)
sortPrivatesByHeight list = runNTimesAllSort (length list * 2) 0 list


--------------------------
-- Part II: Squeezing your Brain Muscles

-- ceremonialFormation: Sorting again, but with multiple files. Don't forget the time!

--ceremonialSort
ceremonialSort :: Int -> [Cell] -> ([Cell], Int)
ceremonialSort slowest cells
    | null first_two = ([], slowest)
    | length first_two == 1 = (cells, slowest)
    | otherwise = case first_two of
        [Full priv_1, Full priv_2]  ->  if height priv_1 < height priv_2 then
                                            let ff_cond = ceremonialSort 0 (snd splited_cells) in
                                                (
                                                    [Full priv_2, Full priv_1] ++ fst ff_cond,
                                                    max (max slowest (max (timeToSwap priv_1) (timeToSwap priv_2))) (snd ff_cond)
                                                )
                                        else
                                            let ff_cond = ceremonialSort 0 (tail cells) in
                                                (
                                                    [Full priv_1] ++ fst ff_cond,
                                                    max slowest (snd ff_cond)
                                                )
        [Empty, Full priv]          ->      let ef_cond = ceremonialSort 0 (snd splited_cells) in
                                                (
                                                    [Full priv, Empty] ++ fst ef_cond,
                                                    max (max slowest (timeToSwap priv)) (snd ef_cond)
                                                )
        [Full priv, Empty]          ->      let fe_cond = ceremonialSort 0 (tail cells) in
                                                (
                                                    [Full priv] ++ fst fe_cond,
                                                    max slowest (snd fe_cond)
                                                )
        
        _                           ->      let ee_ef_cond = ceremonialSort 0 (tail cells) in 
                                                (
                                                    [Empty] ++ fst ee_ef_cond,
                                                    max slowest (snd ee_ef_cond)
                                                )
    where splited_cells = splitAt 2 cells; first_two = fst splited_cells                       

runNTimesCeremonial :: Int -> Int -> [Cell] -> ([Cell], Int)
runNTimesCeremonial n total list --len of Cell, total, [Cell]
    | n <= 0 = (list, total)
    | otherwise = runNTimesCeremonial (n-1) (total + snd one_run) (fst one_run) --n > 0
    where one_run = ceremonialSort 0 list --0 is slowest

ceremonialFormation :: Area -> (Area, Int)
ceremonialFormation area
    | null area = (area, 0)
    | otherwise = ([fst one_run] ++ fst sorted_tail, max (snd one_run) (snd sorted_tail))
    where one_run = runNTimesCeremonial (length (head area) * 2) 0 (head area); sorted_tail = ceremonialFormation (tail area)

-- swapPrivates: Swap two arbitrary privates by ID if they are in the area. Big ouch!

isInCell :: Int -> Int -> [Cell] -> Maybe Int
isInCell id index cell
    | null cell = Nothing
    | otherwise = case head cell of
        Full priv -> if idNumber priv == id then Just index else isInCell id (index + 1) (tail cell)
        _ -> isInCell id (index + 1) (tail cell)

isInArea :: Int -> Int -> Area -> Maybe (Int, Int)
isInArea id index area
    | null area = Nothing
    | otherwise = case isInCell id 0 cell of
        Nothing -> isInArea id (index+1) (tail area)
        Just res -> Just (index, res)
    where cell = head area;

insertElement :: (Int, Int) -> Area -> Cell -> Area
insertElement (x, y) area i_cell = res 
    where cell_lists = splitAt x area; cell_list = head (snd cell_lists); cells = splitAt y cell_list; new_cell_list = fst cells ++ [i_cell] ++ tail (snd cells); res = fst cell_lists ++ [new_cell_list] ++ tail (snd cell_lists)

{- swapPrivates :: Int -> Int -> Area -> Area
swapPrivates id_1 id_2 area
    | null area = area
    | otherwise = case pos_1 of
        Nothing -> area
        Just (x_1, y_1) -> case pos_2 of
            Nothing -> area
            Just (x_2, y_2) -> area
                where element_1 = (area !! x_1) !! y_1; element_2 = (area !! x_2) !! y_2; temp = splitAt x_1 area
    where pos_1 = isInArea id_1 0 area; pos_2 = isInArea id_2 0 area -}

swapPrivates :: Int -> Int -> Area -> Area
swapPrivates id_1 id_2 area
    | null area = area
    | otherwise = case pos_1 of
        Nothing -> area
        Just (x_1, y_1) -> case pos_2 of
            Nothing -> area
            Just (x_2, y_2) -> area_2
                where element_1 = (area !! x_1) !! y_1; element_2 = (area !! x_2) !! y_2; area_1 = insertElement (x_1, y_1) area element_2; area_2 = insertElement (x_2, y_2) area_1 element_1
    where pos_1 = isInArea id_1 0 area; pos_2 = isInArea id_2 0 area

-- Best of luck to you, friend and colleague!
