#!/usr/bin/python3

import example_module

# Create ConnectionFactory
factory = example_module.ConnectionFactory()

# Create connection
conn = factory.create_connection("test")

# Create readers and writers
conn.create_reader("msg1", "topic1")
conn.create_writer("msg2", "topic2")

conn.clear_messages("topic1")

conn.publish_message("topic2", "topic2_msg_file")