//Standard imports
#include<iostream>
#include<fstream>
#include<vector>

//My imports
#include"YAML.hpp"

#define FILE_CONSTEXPR

#pragma once

namespace engine::file {

	class YAMLFile
	{
	private:

		yaml::FileData fileData;
		std::vector<yaml::Node<std::string>> stringNodes;
		std::vector<yaml::Node<float>> floatNodes;

		inline static yaml::ValueType getValueType(std::string value) {
			int index = 0;
			for (char c : value) {
				std::cout << c << std::endl;
				if (c == '\"') {
					return yaml::ValueType::STRING;
				}
				
				if (index == value.size()
					&& c == 'f')
					return yaml::ValueType::FLOAT;

				index++;
			}

			return yaml::ValueType::NOTYPE;
		}

		void readFile(const char *fileName, yaml::FileData &fileData);
		void parseData(yaml::FileData &fileData);

	public:

		YAMLFile(const char *fileName);
		~YAMLFile() = default;

		inline const std::string getString(std::string key) const {
			for (auto node : stringNodes) {
				if (node.key.compare(key))
					return node.value;
			}

			return "";
		}
		inline const float getFloat(std::string key) const {
			
			std::cout << floatNodes.size() << std::endl;

			for (yaml::Node<float> node : floatNodes) {
				if (node.key == key)
					return node.value;
			}

			return -1.f;
		}

	};

};

