namespace engine::file::yaml {

	struct FileData {
		unsigned int fileLength = 0;
		char* dataPointer;
	};

	enum class ValueType {
		NOTYPE = 0,
		STRING = 1,
		FLOAT = 2
	};

	struct PreProcessdData {
		unsigned int fileLength = 0;
		unsigned int num_lines = 0;
		ValueType* lineValueTypes;

	};

	struct Key {
		std::string key;
	};

	/*
		Nodes
	*/
	template<typename T>
	struct Node;

	template<>
	struct Node<std::string> : public Key {
		std::string value;
	};

	template<>
	struct Node<float> : public Key {
		float value;
	};


}