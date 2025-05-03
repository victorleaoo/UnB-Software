from kafka import KafkaConsumer

consumer = KafkaConsumer('input_event', bootstrap_servers=['localhost:9092'])

for msg in consumer:
    print(msg.value)