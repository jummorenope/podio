#include "H5_EventInfoData.h"


H5_EventInfoData::H5_EventInfoData()
{
	cout<<"Registering EventInfoData" << endl;

	h5_datatype = CompType(sizeof(EventInfoData));
	h5_datatype.insertMember("Number", HOFFSET(EventInfoData, Number), H5::PredType::NATIVE_INT);
	hsize_t chunk_dims[2] = {1, 5};
	cparms.setChunk(1, chunk_dims);
	flag = 0;


}


H5_EventInfoData* H5_EventInfoData::getInstance()
{
    if (instance == 0)
    {
        instance = new H5_EventInfoData();
    }

    return instance;
}


std::type_index H5_EventInfoData::get_typeindex()
{
	std::cout << "returning the typeid of EventInfoCollection" <<std::endl;

	return typeid(EventInfoCollection);
}

void H5_EventInfoData::writeCollection(CollectionBase* c, H5File& file)
{

	EventInfoCollection* info = static_cast<EventInfoCollection*>( c );
	// Fill
	void* buffer_1 = info->_getBuffer();
	EventInfoData** data_1 = reinterpret_cast<EventInfoData**>(buffer_1);

	if(flag == 0)
	{
		size[0] = info->size();

		/*
		* Initialize the data space with unlimited dimensions.
		*/
		hsize_t dims[1]  = {info->size()};
		hsize_t maxdims[1] = {H5S_UNLIMITED};
		DataSpace mspace1( RANK_EID, dims, maxdims);

		dataset_eventInfo = file.createDataSet(EVENT_INFO_DATA, h5_datatype, mspace1, cparms);
		DataSpace fspace1 = dataset_eventInfo.getSpace();
		offset[0] = 0;
		hsize_t dims1[1] = {info->size()};            /* data1 dimensions */
		fspace1.selectHyperslab( H5S_SELECT_SET, dims1, offset );

		dataset_eventInfo.extend(size);

		// Write data to file
		dataset_eventInfo.write(*data_1, h5_datatype, mspace1, fspace1);

		// we have written once so set flag = 1
		flag = 1;

	}

	else
	{
		// extend dataset_eventInfo
		hsize_t dim2[1] = {info->size()};

		offset[0] = size[0];
		size[0] += info->size();

		dataset_eventInfo.extend( size );

		// select hyperslab
		DataSpace fspace2 = dataset_eventInfo.getSpace();
		fspace2.selectHyperslab(H5S_SELECT_SET, dim2, offset );

		DataSpace mspace2( RANK_EID, dim2 );

		// Write data to file
		dataset_eventInfo.write(*data_1, h5_datatype, mspace2, fspace2);

	}

}