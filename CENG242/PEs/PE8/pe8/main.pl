:- module(main, [is_movie_directed_by/2, total_awards_nominated/2, all_movies_directed_by/2, total_movies_released_in/3, all_movies_released_between/4]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE

% -------------------- is_movie_directed_by -------------------- %
is_movie_directed_by(Title, Director) :- 
    movie(Title, Director, _, _, _, _).
% -------------------------------------------------------------- %

% ------------------- total_awards_nominated ------------------- %
total_awards_nominated(Title, Nominations) :- 
    movie(Title, _, _, OscarNoms, EmmyNoms, GoldenGlobeNoms),
    Nominations is OscarNoms + EmmyNoms + GoldenGlobeNoms.
% -------------------------------------------------------------- %

% ------------------- all_movies_directed_by ------------------- %
all_movies_directed_by(Director, Movies) :- 
    findall(Title, movie(Title, Director, _, _, _, _), Movies).
% -------------------------------------------------------------- %

% ------------------ total_movies_released_in ------------------ %
total_movies_released_in([], _, 0) :- !.
total_movies_released_in([Title | TailMovies], Year, Count) :- 
    movie(Title, _, Year_of_Title, _, _ ,_),
    Year_of_Title =:= Year,
    total_movies_released_in(TailMovies, Year, Tail_Count), !,
    Count is Tail_Count + 1.
total_movies_released_in([Title | TailMovies], Year, Count) :- 
    movie(Title, _, Year_of_Title, _, _ ,_),
    Year_of_Title =\= Year,
    total_movies_released_in(TailMovies, Year, Tail_Count), !,
    Count is Tail_Count.
% -------------------------------------------------------------- %

% ----------------- all_movie_released_between ----------------- %
all_movies_released_between([], _, _, []) :- !.
all_movies_released_between([Title | Tail_Movies], MinYear, MaxYear, [Title | Tail_Between]) :-
    movie(Title, _, Year, _, _, _),
    MaxYear >= Year,
    MinYear =< Year,
    all_movies_released_between(Tail_Movies, MinYear, MaxYear, Tail_Between), !.
all_movies_released_between([Title | Tail_Movies], MinYear, MaxYear, MoviesBetweenGivenYears) :-
    all_movies_released_between(Tail_Movies, MinYear, MaxYear, MoviesBetweenGivenYears), !.
% -------------------------------------------------------------- %
