from kafka import KafkaProducer

if __name__ == '__main__':
    producer = KafkaProducer(bootstrap_servers='localhost:9092')
    print("producer created")
    for i in range(100):
        print("writing message")
        producer.send(topic='transactions', value=b't')
    producer.flush()
