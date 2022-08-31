module PE2 where

import Text.Printf

type Point = (Int, Int)
type Dimensions = (Int, Int)
type Vector = (Int, Int)

getRounded :: Double -> Double
getRounded x = read s :: Double
               where s = printf "%.2f" x

castIntToDouble x = (fromIntegral x) :: Double

-------------------------------------------------------------------------------------------
----------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------
getVector :: String -> Vector
getVector d
    | d == "North" = (0, 1)
    | d == "East" = (1, 0)
    | d == "South" = (0, -1)
    | d == "West" = (-1, 0)
    | d == "NorthEast" = (1, 1)
    | d == "NorthWest" = (-1, 1)
    | d == "SouthEast" = (1, -1)
    | d == "SouthWest" = (-1, -1)
    | otherwise  = (0, 0)

-------------------------------------------------------------------------------------------------------------------------------
getAllVectors :: [String] -> [Vector]
getAllVectors l = [getVector d | d <- l]

-------------------------------------------------------------------------------------------------------------------------------

producePath :: Point -> [String] -> [Point]
producePath initial actions = case actions of
    [] -> [initial]
    _ -> initial : producePath new_initial (tail actions)
    where action = getVector (head actions); new_initial = (fst initial + fst action, snd initial + snd action)

-------------------------------------------------------------------------------------------------------------------------------
takePathInArea :: [Point] -> Dimensions -> [Point]
takePathInArea path (bx, by)
    | null path = []
    | fst vec < bx && fst vec >= 0 && snd vec < by && snd vec >= 0 = vec : takePathInArea (tail path) (bx, by)
    | otherwise = []
    where vec = head path

-------------------------------------------------------------------------------------------------------------------------------

remainingObjectsHelper :: [Point] -> Dimensions -> [Point] -> [Point]
remainingObjectsHelper pickable_items border objects
    | null objects = []
    | elem (head objects) pickable_items = remainingObjectsHelper pickable_items border (tail objects)
    | otherwise = head objects : remainingObjectsHelper pickable_items border (tail objects)


remainingObjects :: [Point] -> Dimensions -> [Point] -> [Point]
remainingObjects path border objects = remainingObjectsHelper pickable_items border objects
    where pickable_items = takePathInArea path border

-------------------------------------------------------------------------------------------------------------------------------

averageStepsHelper :: [[Point]] -> Int -> Int 
averageStepsHelper succ_paths total
    | null succ_paths = total
    | otherwise = averageStepsHelper (tail succ_paths) (total + length (head succ_paths))

averageStepsInSuccess :: [[Point]] -> Dimensions -> [Point] -> Double
averageStepsInSuccess paths border objects = castIntToDouble (averageStepsHelper succ_paths 0) / castIntToDouble (length succ_paths)
    where succ_paths = [path | path <- paths, length path == length (takePathInArea path border)]
