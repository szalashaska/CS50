SELECT title FROM movies
JOIN ratings ON movies.id = ratings.movie_id
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE UPPER(people.name) = "CHADWICK BOSEMAN"
ORDER BY ratings.rating DESC LIMIT 5;