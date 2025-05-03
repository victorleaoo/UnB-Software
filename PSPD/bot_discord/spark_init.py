#create SC with the specified configuration
def spark_context_creator():
    conf = SparkConf()
    #set name for our app
    conf.setAppName("KafkaTest")
    #The master URL to connect
    conf.setMaster('spark://localhost:8080')
    sc = None
    try:
        sc.stop()
        sc = SparkContext(conf=conf)
    except:
        sc = SparkContext(conf=conf)
    return sc

sc = spark_context_creator()
#To avoid unncessary logs
sc.setLogLevel("WARN")