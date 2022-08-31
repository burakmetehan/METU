module PE4 where

import Data.List
import Data.Maybe

data Room = SeedStorage Int
          | Nursery Int Int
          | QueensChambers
          | Tunnel
          | Empty
          deriving Show

data Nestree = Nestree Room [Nestree] deriving Show

---------------------------------------------------------------------------------------------
------------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
--------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
--------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
---------------------------------------------------------------------------------------------

-- Note: undefined is a value that causes an error when evaluated. Replace it with
-- a viable definition! Name your arguments as you like by changing the holes: _

---------------------------------------------------------------------------------------------

-------------------------------------------Q1-------------------------------------------
-- Q1: Calculate the nutrition value of a given nest.
nestNutritionValue :: Nestree -> Int
nestNutritionValue tree = case tree of
  (Nestree (SeedStorage value) []) -> value * 3
  (Nestree (Nursery value_1 value_2) []) -> value_1 * 7 + value_2 * 10
  (Nestree _ []) -> 0
  (Nestree (SeedStorage value) tree_list) -> value * 3 + sum [nestNutritionValue subtree | subtree <- tree_list]
  (Nestree (Nursery value_1 value_2) tree_list) -> value_1 * 7 + value_2 * 10 + sum [nestNutritionValue subtree | subtree <- tree_list]
  (Nestree _ tree_list) -> 0 + sum [nestNutritionValue subtree | subtree <- tree_list]


-------------------------------------------Q2-------------------------------------------

-- Q2: Calculate the nutrition value of each root-to-leaf path.
pathNutritionValues :: Nestree -> [Int]
pathNutritionValues tree = case tree of
  (Nestree (SeedStorage value) []) -> [value * 3]
  (Nestree (Nursery value_1 value_2) []) -> [value_1 * 7 + value_2 * 10]
  (Nestree _ []) -> [0]
  (Nestree (SeedStorage value) tree_list) -> [value * 3 + x | x <- concat [pathNutritionValues subtree | subtree <- tree_list]]
  (Nestree (Nursery value_1 value_2) tree_list) -> [value_1 * 7 + value_2 * 10 + x | x <- concat [pathNutritionValues subtree | subtree <- tree_list]]
  (Nestree _ tree_list) -> [0 + x | x <- concat [pathNutritionValues subtree | subtree <- tree_list]]


-------------------------------------------Q3-------------------------------------------
myMinimum :: [Maybe Int] -> Maybe Int
myMinimum list
  | null list = Nothing
  | otherwise = minimum list

justAdder :: Maybe Int -> Maybe Int -> Maybe Int
justAdder val_1 val_2 = case val_1 of
  Nothing -> Nothing
  Just value_1 -> case val_2 of
    Nothing -> Nothing
    Just value_2 -> Just (value_1 + value_2)


-- Q3: Find the depth of the shallowest tunnel, if you can find one.
shallowestTunnel :: Nestree -> Maybe Int
shallowestTunnel tree = case tree of
  (Nestree Tunnel _) -> Just 1
  (Nestree _ []) -> Nothing
  (Nestree _ tree_list) -> let sub_tree_tunnel = myMinimum [x | x <- [shallowestTunnel subtree | subtree <- tree_list], isJust x] in
    if isJust sub_tree_tunnel then justAdder (Just 1) sub_tree_tunnel else Nothing


-------------------------------------------Q4-------------------------------------------
-- Q4: Find the path to the Queen's Chambers, if such a room exists.
pathToQueen :: Nestree -> Maybe [Room]
pathToQueen tree = case tree of
  (Nestree QueensChambers _) -> Just []
  (Nestree _ []) -> Nothing
  (Nestree room tree_list) -> let sub_tree_path = catMaybes [pathToQueen subtree | subtree <- tree_list] in
    if null sub_tree_path then Nothing else Just (room : concat sub_tree_path)


-------------------------------------------Q5-------------------------------------------
elemTunnel :: [Room] -> Int -> [Int]
elemTunnel list index
  | null list = []
  | otherwise = case head list of
    Tunnel -> index : elemTunnel (tail list) (index + 1)
    _ -> elemTunnel (tail list) (index + 1)

-- Q5: Find the quickest depth to the Queen's Chambers, including tunnel-portation :)
quickQueenDepth :: Nestree -> Maybe Int
quickQueenDepth tree = let path = pathToQueen tree in case path of
                         Nothing -> Nothing 
                         Just _ -> let new_path = concat path; tunnels = elemTunnel new_path 0 in case tunnels of 
                                     [] -> Just (length new_path + 1)
                                     _ -> let min_tunnel = fromJust (shallowestTunnel tree); last_tunnel = last tunnels in
                                       -- We know there is tunnel on path so at least one tunnel, no chance for nothing in shallowest Tunnel
                                       if min_tunnel == last_tunnel + 1 then Just (length new_path + 1) else Just (length new_path - last_tunnel + min_tunnel) 


-- Example nest given in the PDF.
exampleNest :: Nestree
exampleNest =
  Nestree Tunnel [
    Nestree (SeedStorage 15) [
      Nestree (SeedStorage 81) []
    ],
    Nestree (Nursery 8 16) [
      Nestree Tunnel [
        Nestree QueensChambers [
          Nestree (Nursery 25 2) []
        ]
      ]
    ],
    Nestree Tunnel [
      Nestree Empty [],
      Nestree (SeedStorage 6) [
        Nestree Empty [],
        Nestree Empty []
      ]
    ]
  ]

-- Same example tree, with tunnels replaced by Empty
exampleNestNoTunnel :: Nestree
exampleNestNoTunnel =
  Nestree Empty [
    Nestree (SeedStorage 15) [
      Nestree (SeedStorage 81) []
    ],
    Nestree (Nursery 8 16) [
      Nestree Empty [
        Nestree QueensChambers [
          Nestree (Nursery 25 2) []
        ]
      ]
    ],
    Nestree Empty [
      Nestree Empty [],
      Nestree (SeedStorage 6) [
        Nestree Empty [],
        Nestree Empty []
      ]
    ]
  ]
