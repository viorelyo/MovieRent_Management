# MovieRent_Management
In order not to miss good movies, you absolutely need a software application that allows you to manage movies and watchlists (C++ Uni Assignment)

## Getting started
The application `MOVIX` (pseudo-ChatBot) can be used in two ways: administratorMode and userMode. When the application is started it offers the possibility to choose the mode.
* An user can create a watchlist of the movies he wants to see.
* The application allows the admin to update the database.

<img src="/screenshots/gif2.gif" width="700">


## Prerequisites
* Visual Studio
* C++ Tools
* Windows SDK Version 10.0.14393.0
* Win32 API ( `<Windows.h>` )

## Features
- UserMode
    - Watch all movies of a `selected genre`
    - Manage own `Watchlist`
    - Watch the `trailers` of the wanted movies
    - `Save` watchlist in `html / csv` format
- AdminMode
    - `CRUD` operations   

## Demo
Log In as Administrator  
P.S. the default Credentials: Username: `admin` Password: `1111`  
Here comes the admin Menu.  

<img src="/screenshots/gif1.gif" width="700">

Log In as User  
Users are saved into a local database (.csv file)  
You can watch the movies by the genre and select which of them to add to own wathlist.  
The movielist is iterated and user can choose a movie from it.  
You can watch the trailer for a movie.  

<img src="/screenshots/gif3.gif" width="700">

User can access his watchlist

<img src="/screenshots/gif4.gif" width="700">

The watchlist can also be rendered in `html` format

<img src="/screenshots/screenshot1.PNG" width="700">



