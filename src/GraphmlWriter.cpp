#include "../include/GraphmlWriter.h"
#include "../include/Builder.h"
#include <fstream>
#include <sstream>
#include <unordered_set>

using namespace llvm2graphml;

static void fillInKeys(const Properties &properties,
                       std::unordered_map<std::string, std::unordered_set<std::string>> &keys) {
  for (auto &pair : properties.getStrings()) {
    keys["string"].insert(pair.first);
  }
  for (auto &pair : properties.getBooleans()) {
    keys["boolean"].insert(pair.first);
  }
  for (auto &pair : properties.getLongs()) {
    keys["long"].insert(pair.first);
  }
}

static void emitKeys(std::stringstream &stream,
                     std::unordered_map<std::string, std::unordered_set<std::string>> &keys,
                     const std::string &kind) {
  for (const auto &bucket : keys) {
    const std::string &propertyType = bucket.first;
    for (const std::string &propertyName : bucket.second) {
      stream << "  <key id='" << propertyName << "' for='" << kind << "' attr.name='"
             << propertyName << "' attr.type='" << propertyType << "'></key>\n";
    }
  }
}

static void emitData(std::stringstream &stream, const Properties &properties) {
  std::unordered_map<std::string, std::string> data;
  for (auto &pair : properties.getStrings()) {
    data[pair.first] = pair.second;
  }
  for (auto &pair : properties.getLongs()) {
    data[pair.first] = std::to_string(pair.second);
  }
  for (auto &pair : properties.getBooleans()) {
    data[pair.first] = (pair.second ? "true" : "false");
  }

  for (const auto &pair : data) {
    stream << "    <data key='" << pair.first << "'>" << pair.second << "</data>\n";
  }
}

void GraphmlWriter::saveGraph(const Builder &builder, const std::string &output) {
  std::unordered_map<std::string, std::unordered_set<std::string>> nodeKeys;
  for (const std::unique_ptr<Node> &node : builder.getNodes()) {
    fillInKeys(node->getProperties(), nodeKeys);
  }

  std::unordered_map<std::string, std::unordered_set<std::string>> edgeKeys;
  for (const std::unique_ptr<Edge> &edge : builder.getEdges()) {
    fillInKeys(edge->getProperties(), edgeKeys);
  }

  std::stringstream keys;
  emitKeys(keys, nodeKeys, "node");
  emitKeys(keys, edgeKeys, "edge");

  std::stringstream nodes;
  for (const std::unique_ptr<Node> &node : builder.getNodes()) {
    nodes << "  <node id='" << node->getID() << "'>\n";
    emitData(nodes, node->getProperties());
    nodes << "  </node>\n";
  }

  std::stringstream edges;
  for (const std::unique_ptr<Edge> &edge : builder.getEdges()) {
    nodes << "  <edge id='" << edge->getID() << "' source='" << edge->getSourceID() << "' target='"
          << edge->getTargetID() << "'>\n";
    emitData(nodes, edge->getProperties());
    nodes << "  </edge>\n";
  }

  std::fstream graph(output, std::fstream::trunc | std::fstream::out);
  graph << "<?xml version='1.0' ?>\n";
  graph << "<graphml xmlns='http://graphml.graphdrawing.org/xmlns'>\n";
  graph << keys.str() << "\n";
  graph << "  <graph id='llvm' edgedefault='directed'>\n";
  graph << nodes.str() << "\n";
  graph << "</graph>\n";
  graph << "</graphml>\n";
}
