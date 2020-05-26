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

	struct NodeData {
		ValueType type;
		unsigned int num_chars_to_value = 0; //This is from the colon
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