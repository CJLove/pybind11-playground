#include <memory>
#include <string>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <spdlog/spdlog.h>

namespace py = pybind11;

class Connection {
public:
    using Messages = std::vector<std::string>;

    Connection(const std::string &name):
        m_name(name)
    {}

    ~Connection() = default;

    void createReader(const std::string &messageType, const std::string &topic)
    {
        SPDLOG_INFO("Creating reader for message {} on topic {}", messageType, topic);
    }

    void createWriter(const std::string &messageType, const std::string &topic)
    {
        SPDLOG_INFO("Creating writer for message {} on topic {}", messageType, topic);
    }

    void clearMessages(const std::string &topic)
    {
        SPDLOG_INFO("Clearing received messages for topic {}", topic);
    }

    Messages getMessages(const std::string &topic)
    {
        SPDLOG_INFO("Returning received messages for topic {}", topic);
        return {
            "Message1",
            "Message2",
            "Message3"
        };
    }

    void publishMessage(const std::string &topic, const std::string &messageFile)
    {
        SPDLOG_INFO("Publishing message {} to topic {}", messageFile, topic);
    }

private:
    std::string m_name;
};

class ConnectionFactory {
public:
    std::unique_ptr<Connection> createConnection(const std::string &name) {
        SPDLOG_INFO("Creating Connection for {}", name);
        return std::make_unique<Connection>(name);
    }

};

// The module name here must match the target name in CMakeLists.txt
PYBIND11_MODULE(example_module, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    // Bind the Item class first so pybind11 knows about it
    py::class_<Connection>(m, "Connection")
        .def(py::init<const std::string &>())
        .def("create_reader", &Connection::createReader)
        .def("create_writer", &Connection::createWriter)
        .def("clear_messages", &Connection::clearMessages)
        .def("get_messages", &Connection::getMessages)
        .def("publish_message", &Connection::publishMessage);

    // Bind the Factory class and its methods
    py::class_<ConnectionFactory>(m, "ConnectionFactory")
        .def(py::init<>())
        .def("create_connection", &ConnectionFactory::createConnection); 
}
