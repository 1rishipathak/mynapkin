The folder contains a .db file has a relational database that has various tables ( directors, movies, people, ratings, stars) with each table having various interlinked keys and columns.
Each .sql file extracts specific data (as indicated by the comment in the header) from the .db file using SQL queries.

To print the output of a given SQL query (.sql file) into a .txt file, the following can be executed in the CLI:
cat [filename.sql] | sqlite3 movies.db
