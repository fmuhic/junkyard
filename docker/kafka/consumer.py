from kafka import KafkaConsumer
from pprint import pprint

if __name__ == '__main__':
    consumer = KafkaConsumer(
        'transactions',
        bootstrap_servers=['localhost:9092'],
        group_id="k2n4j_consumers"
    )
    for msg in consumer:
        # Store to neo4j + proper error handling
        pprint(msg)
