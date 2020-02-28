#include <stddef.h>
#include <vector>
#include <boost/serialization/access.hpp>
#include "ActivationFunctions.h"

namespace netk
{
	struct Link
	{
		float mWeight;        // The connection weight 
		int mInputNodeIndex;  // The index for the start node of the link
		int mOutputNodeIndex; // The imdex for the end node of the link

		// The number of memory in bytes this object uses
		size_t TotalSize() const { return sizeof(*this); }

		// Boost serialization support
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & mWeight;
			ar & mInputNodeIndex;
			ar & mOutputNodeIndex;
		}
	};
	
	typedef float(*ActivationFuncPtr)(float, void*);

	class Node
	{
	public:
		enum class Type { Input, Hidden, Output };
		Type GetType() const { return mType; }

		// The number of memory in bytes this object uses
		size_t TotalSize() const;

		// Metadata manipulation
		template<typename MetadataT>
		MetadataT* GetMetadata() { return  static_cast<MetadataT*>(mMetadata); }
		void SetMetadata(void* metadata) { mMetadata = metadata; }
	private:
		ActivationFuncPtr mActivationF = NEATSigmoid;
		Type mType = Type::Hidden;
		void* mMetadata = nullptr; // Metadata is an optional user defined payload. It's NOT serialized and the user is responsible of handling the memory

		// Boost serialization support
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & mType;
			ar & mIncomingLinks;
			ar & mOutgoingLinks;
			// TODO : find how to serialize the activation function
		}

		// Memory could be saved here by storing the links on an array, at the cost of an indirection and uglier code
		std::vector<Link> mIncomingLinks;
		std::vector<Link> mOutgoingLinks;
	};

}