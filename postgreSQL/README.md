# PostgreSQL stuff

## Setup
Run commands to create simple setup
```sh
$docker run --name pgtest -e POSTGRES_PASSWORD=postgres postgres
$docker exec -it pgtest bash

# inside container create table and insert 1M rows
$psql -U postgres
$create table grades (id serial not null, grade int not null);
$insert into grades(grade) select floor(random() * 100) from generate_series(0, 1000000)
```
