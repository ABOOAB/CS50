create table new_students(
    id integer,
    student_name text,
    primary key(id)
);

create table houses(
    id integer,
    house text,
    head text,
    primary key(id)
);

create table assignments(
    name_id integer,
    house_id integer,
    foreign key(name_id) references new_name(id) ,
    foreign key(house_id) references houses(id)
);
