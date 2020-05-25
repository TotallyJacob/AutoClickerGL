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

		yaml::PreProcessdData preProcessedData;
		yaml::FileData fileData;
		std::vector<yaml::Node<std::string>> stringNodes;
		std::vector<yaml::Node<float>> floatNodes;

		inline static yaml::ValueType getValueType(std::string &value) {
			int index = 0;
			for (char c : value) {
				if (c == '\"') {
					return YAMLType::STRING;
				}
				
				if (index == value.size()
					&& c == 'f')
					return YAMLType::FLOAT;

				index++;
			}

			return YAMLType::NOTYPE;
		}

		void readFile(const char *fileName, yaml::FileData &fileData);
		void parseData(yaml::FileData &fileData);

		//Pre processing
		constexpr void preReadFile(const char* fileName) const;
		constexpr void preProcessFile(yaml::PreProcessdData &preProcessedData, char *data, unsigned int size) const;

	public:

		YAMLFile(const char *fileName);
		~YAMLFile() = default;

		inline const std::string getString(std::string key) const {
			for (auto node : stringNodes) {
				if (node.key == key)
					return node.value;
			}

			return "";
		}
		inline const float getFloat(std::string key) const {
			for (auto node : floatNodes) {
				if (node.key == key)
					return node.value;
			}

			return -1.f;
		}

	};

};

