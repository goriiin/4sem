import random

import psycopg2
from faker import Faker
from psycopg2.extras import DictCursor

fake = Faker()

# Database connection settings
DB_HOST = 'localhost'
DB_NAME = 'database_cw'
DB_USER = 'dmitry'
DB_PASSWORD = '123'

# Connect to the database
conn = psycopg2.connect(
    host=DB_HOST,
    database=DB_NAME,
    user=DB_USER,
    password=DB_PASSWORD,
    cursor_factory=DictCursor
)
cur = conn.cursor()

# Populate registration_address table
for i in range(1, 1000):
    city = fake.city()
    street = fake.street_name()
    house_num = fake.building_number()
    flat = fake.random_int(1, 100)
    country = fake.country()
    cur.execute(
        "INSERT INTO registration_address"
        "(id, city, street, house_num, flat, country) "
        "VALUES (%s, %s, %s, %s, %s, %s)",
        (i, city, street, house_num, flat, country))

conn.commit()

# Populate human table
for i in range(1, 1000):
    surname = fake.last_name()
    name = fake.first_name()
    mid_name = fake.first_name() + "ovich"  # generate a middle name
    passport_series = fake.random_int(1000, 9999)
    passport_num = fake.random_int(100000, 999999)
    birthday = fake.date_of_birth()
    reg_address_id = fake.random_int(1, 100)
    cur.execute("INSERT INTO human "
                "(id, surname, name, mid_name, passport_series, passport_num, birthday, reg_address) "
                "VALUES (%s, %s, %s, %s, %s, %s, %s, %s)",
                (i, surname, name, mid_name, passport_series, passport_num, birthday, reg_address_id))

conn.commit()

# Populate bank_data table
for i in range(1, 1000):
    num = fake.credit_card_number()
    date = fake.credit_card_expire()
    cvc = fake.random_int(100, 999)
    cur.execute("INSERT INTO bank_data"
                "(id, num, date, cvc)"
                " VALUES (%s,%s, %s, %s)",
                (i, num, date, cvc))

conn.commit()

def generate_phone_number():
    return f"79{random.randint(10000000, 99999999)}"

def generate_email(i):
    i %= 3
    if i == 0:
        return fake.free_email()
    if i == 1:
        return fake.safe_email()
    if i == 2:
        return fake.company_email()

# # Populate user table
for i in range(1, 1000):
    nick = fake.user_name() +f"{i}"
    bank_data_id = fake.random_int(1, 100)
    email = generate_email(i)
    phone_number = generate_phone_number()
    reg_date = fake.date_time()
    human_id = fake.random_int(1, 100)
    cur.execute("INSERT INTO \"user\" "
                "(id, nick, bank_data, email, phone_number, reg_date, human_id) "
                "VALUES (%s,%s, %s, %s, %s, %s, %s)",
                (i, nick, bank_data_id, email, phone_number, reg_date, human_id))

conn.commit()

# Populate fine table
for i in range(1, 1000):
    _sum = fake.random_int(100, 1000)
    description = fake.text()
    cur.execute("INSERT INTO fine "
                "(id, sum, description) "
                "VALUES (%s,%s, %s)",
                (i, _sum, description))

conn.commit()

# # Populate user_fines table
for i in range(1, 1000):
    user_id = fake.random_int(1, 100)
    fine_id = fake.random_int(1, 100)
    date = fake.date_time()
    cur.execute("INSERT INTO user_fines "
                "(id, user_id, fine_id, date) "
                "VALUES (%s,%s, %s, %s)",
                (i, user_id, fine_id, date))

conn.commit()

# # Populate driver_license table
for i in range(1, 1000):
    _type = fake.random_element(['A', 'B', 'C'])
    begin_date = fake.date_time()
    end_date = fake.date_time()
    num = fake.license_plate()
    cur.execute("INSERT INTO driver_license "
                "(id, type, begin_date, end_date, num) "
                "VALUES (%s, %s, %s, %s, %s)",
                (i, _type, begin_date, end_date, num))

conn.commit()

# # Populate user_license table
for i in range(1, 1000):
    user_id = fake.random_int(1, 100)
    licence_id = fake.random_int(1, 100)
    cur.execute("INSERT INTO user_license "
                "(id, user_id, licence_id) "
                "VALUES (%s,%s, %s)",
                (i, user_id, licence_id))

conn.commit()

# Populate transport_info table
for i in range(1, 1000):
    brand = fake.company()
    release_year = fake.random_int(2000, 2022)
    model = fake.sentence(nb_words=2)
    license_level = fake.random_element(['A', 'B', 'C'])
    cur.execute("INSERT INTO transport_info"
                "(id, brand, release_year, model, license_level) "
                "VALUES (%s,%s, %s, %s, %s)",
                (i, brand, release_year, model, license_level))

conn.commit()

# Populate damage table
for i in range(1, 1000):
    machine_part = fake.random_element(['engine', 'transmission', 'brakes'])
    description = fake.text()
    severity = fake.random_int(1, 5)
    cur.execute("INSERT INTO damage "
                "(id, machine_part, description, severity) "
                "VALUES (%s,%s, %s, %s)",
                (i, machine_part, description, severity))

conn.commit()

# # Populate general_info table
for i in range(1, 2000):
    checkup_date = fake.random_int(1, 12)
    engine_type = fake.random_element(['gasoline', 'diesel', 'electric'])
    color = fake.color_name()
    description = fake.text()
    cur.execute("INSERT INTO general_info"
                "(id, checkup_date, engine_type, color, description)"
                "VALUES (%s,%s, %s, %s, %s)",
                (i, checkup_date, engine_type, color, description))

conn.commit()

# # Populate transport table
for i in range(1, 1000):
    general_info_id = fake.random_int(1, 100)
    transport_info_id = fake.random_int(1, 100)
    free = fake.boolean()
    state_number = fake.license_plate()
    date_add = fake.date_time()
    cur.execute("INSERT INTO transport"
                "(id, general_info_id, transport_info_id, free, state_number, date_add) "
                "VALUES (%s,%s, %s, %s, %s, %s)",
                (i, general_info_id, transport_info_id, free, state_number, date_add))

conn.commit()

# # Populate transport_damages table
for i in range(1, 1000):
    transport_id = fake.random_int(1, 100)
    damage_id = fake.random_int(1, 100)
    cur.execute("INSERT INTO transport_damages "
                "(id, transport_id, damage_id) "
                "VALUES (%s,%s, %s)",
                (i, transport_id, damage_id))

conn.commit()

# Populate rent table
for i in range(1, 1000):
    transport_id = fake.random_int(1, 100)
    user_id = fake.random_int(1, 100)
    cost_per_hour = fake.random_int(100, 1000)
    begin_date = fake.date_time()
    end_date = fake.date_time()
    city = fake.city()
    cur.execute("INSERT INTO rent"
                "(id, transport_id, user_id, cost_per_hour, begin_date, end_date, city) "
                "VALUES (%s,%s, %s, %s, %s, %s, %s)",
                (i, transport_id, user_id, cost_per_hour, begin_date, end_date, city))

# Commit the changes
conn.commit()

# Close the cursor and connection
cur.close()
conn.close()


