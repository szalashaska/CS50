CREATE TABLE stocks (
stocks_id INTEGER,
stock_name TEXT NOT NULL,
quantity INTEGER,
user_id INTEGER NOT NULL,
PRIMARY KEY(stocks_id),
FOREIGN KEY(user_id) REFERENCES users(id)
);

CREATE TABLE history (
history_id INTEGER,
stock_name TEXT NOT NULL,
quantity INTEGER,
price NUMERIC NOT NULL,
timestamp TIMESTAMP,
user_id INTEGER NOT NULL,
PRIMARY KEY(history_id),
FOREIGN KEY(user_id) REFERENCES users(id)
);

CREATE TABLE quote (
quote_id INTEGER,
name TEXT,
symbol TEXT NOT NULL,
user_id INTEGER NOT NULL,
PRIMARY KEY(quote_id),
);



INSERT INTO history (stock_name, quantity, price, timestamp, user_id) VALUES ("aloha"", 15, 55.60, CURRENT_TIMESTAMP, 101);

INSERT INTO stocks (stock_name, quantity, user_id) VALUES ("Aasx", 2, 50);

INSERT INTO users (username, hash) VALUES ("elo", "hash");