from datetime import datetime
import config
from psycopg2 import connect, sql

# Tools I used in the app.py server. 

# Returns a conn and a cursor
def load():
    # Connect to C2
    try:
        conn = connect(dbname=config.database, user=config.username,
                       password=config.password, host=config.host, port=config.port, connect_timeout=20)
        cursor = conn.cursor()
    except:
        print("failed to connect")

    return conn, cursor

def insertQueryBuilder(tableName, columns):

    q = sql.SQL("INSERT INTO {table}({column}) VALUES ({value})").format(
        table=sql.Identifier(tableName),
        column=sql.SQL(',').join([
            sql.Identifier(x) for x in columns
        ]),
        value=sql.SQL(',').join(sql.Placeholder() * len(columns))
    )

    return q


def insertQueryBuilder(tableName, columns, returnStringList):

    q = sql.SQL("INSERT INTO {table}({column}) VALUES ({value}) RETURNING {returnThis}").format(
        table=sql.Identifier(tableName),
        column=sql.SQL(',').join([
            sql.Identifier(x) for x in columns
        ]),
        value=sql.SQL(',').join(sql.Placeholder() * len(columns)),
        returnThis=sql.SQL(',').join([
            sql.Identifier(x) for x in returnStringList
        ]
        )
    )
    return q


# Executes an insert query
def executeInsertQuery(query, variables):
    try:
        conn, cursor = load()
        cursor.execute(query, variables)
        conn.commit()
        response = cursor.fetchall()
        cursor.close()
        conn.close()
        return response
    except Exception as error:
        print(f"error on execute insert query: {error}")

# Executes some generic query with variables
def executeGenericVar(query, variables):
    try: 
        conn, cursor = load() 
        cursor.execute(query, variables)
        conn.commit()
        response = cursor.fetchall()
        cursor.close()
        conn.close()   
        return response 
    except Exception as error:
        print(f"error on execute generic query: {error}")

def executeMany(query, values):
    try:
        conn, cursor = load()
        cursor.executemany(query, values)
        conn.commit()

        response = cursor.fetchall()
        cursor.close()
        conn.close()

        return response
    except Exception as error:
        print(f"error on execute Many: {error}")
    
# Executes a select query
def executeSelectQueryVars(query, variables):
    try:
        conn, cursor = load()
        cursor.execute(query, (variables),)
        conn.commit()
        returnThis = cursor.fetchall()
        cursor.close()
        conn.close()
        return returnThis

    except Exception as e:
        print(f"error on execute select query: {e}")


def executeSelectQuery(query):
    try:
        conn, cursor = load()
        cursor.execute(query)
        conn.commit()
        returnThis = cursor.fetchall()
        cursor.close()
        conn.close()
        return returnThis
    except Exception as e:
        print(f"\n\nerror on execute select query: {e}\n\n")

def updateLastSeen(id: int):
    time = [datetime.now(tz=None)] 
    column = ["last_seen"]
    query = insertQueryBuilder("implants", column, ["implant_id"])
    response = executeInsertQuery(query, time) 