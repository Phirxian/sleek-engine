/************************************************************************************
This source file is part of the Theora Video Playback Library
For latest info, see http://libtheoraplayer.sourceforge.net/
*************************************************************************************
Copyright (c) 2008-2010 Kresimir Spes (kreso@cateia.com)
This program is free software; you can redistribute it and/or modify it under
the terms of the BSD license: http://www.opensource.org/licenses/bsd-license.php
*************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS // MSVC++

#include <memory.h>
#include <iostream>

#include "TheoraDataSource.h"
#include "TheoraException.h"

TheoraDataSource::~TheoraDataSource()
{

}

TheoraFileDataSource::TheoraFileDataSource(std::string filename)
{
	mFilename=filename;
	mFilePtr.open(mFilename.c_str(), std::ios::in | std::ios::binary);

	if(!mFilePtr.is_open())
	{
        throw TheoraGenericException("Can't open video file: "+filename);
	}

	mFilePtr.seekg(0, mFilePtr.end);
	mSize=mFilePtr.tellg();
	mFilePtr.seekg(0, mFilePtr.beg);
}

TheoraFileDataSource::~TheoraFileDataSource()
{
    mFilePtr.close();
}

int TheoraFileDataSource::read(void* output,int nBytes)
{
    return mFilePtr.read((char*)output, nBytes).gcount();
}

void TheoraFileDataSource::seek(unsigned long byte_index)
{
    mFilePtr.seekg(byte_index, mFilePtr.beg);
}

unsigned long TheoraFileDataSource::size()
{
	return mSize;
}

unsigned long TheoraFileDataSource::tell()
{
	return mFilePtr.tellg();
}

TheoraMemoryFileDataSource::TheoraMemoryFileDataSource(std::string filename) :
	mReadPointer(0),
	mData(0)
{
	std::ifstream mFilePtr;
	mFilename=filename;
	mFilePtr.open(mFilename.c_str(), std::ios::in | std::ios::binary);

	if(!mFilePtr.is_open())
	{
        throw TheoraGenericException("Can't open video file: "+filename);
	}

	mFilePtr.seekg(0, mFilePtr.end);
	mSize=mFilePtr.tellg();
	mFilePtr.seekg(0, mFilePtr.beg);

	mData=new unsigned char[mSize];
    mFilePtr.read((char*)mData, mSize);

    mFilePtr.close();
}

TheoraMemoryFileDataSource::~TheoraMemoryFileDataSource()
{
	if (mData) delete [] mData;
}

int TheoraMemoryFileDataSource::read(void* output,int nBytes)
{
	int n=(mReadPointer+nBytes <= mSize) ? nBytes : mSize-mReadPointer;
	if (!n) return 0;
	memcpy(output,mData+mReadPointer,n);
	mReadPointer+=n;
	return n;
}

void TheoraMemoryFileDataSource::seek(unsigned long byte_index)
{
	mReadPointer=byte_index;
}

unsigned long TheoraMemoryFileDataSource::size()
{
	return mSize;
}

unsigned long TheoraMemoryFileDataSource::tell()
{
	return mReadPointer;
}
