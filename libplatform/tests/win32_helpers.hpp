#pragma once

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <exception>

const platform::string_t fname = STR("myfilename");

const char junk_data[] = "foobarbaz";
const int junk_size = sizeof(junk_data);

// Create an empty file
static bool create_empty_file(const platform::string_t &filename)
{
	HANDLE h = CreateFile(filename.c_str(), GENERIC_READ | GENERIC_WRITE, 0,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h == INVALID_HANDLE_VALUE) {
		throw std::exception("Failed to create file");
	}

	CloseHandle(h);

	return true;
}

static bool create_junk_file(const platform::string_t &filename)
{
	DWORD written = 0;
	HANDLE h = CreateFile(filename.c_str(), GENERIC_READ | GENERIC_WRITE, 0,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h == INVALID_HANDLE_VALUE) {
		throw std::exception("Failed to create file");
	}

	BOOL rc = WriteFile(h, junk_data, junk_size, &written, NULL);
	if(!rc){
		throw std::exception("Failed to write data");
	}

	CloseHandle(h);

	return rc;
}

static bool file_exists(const platform::string_t &filename)
{
	WIN32_FILE_ATTRIBUTE_DATA data;
	BOOL rc = GetFileAttributesEx(filename.c_str(), GetFileExInfoStandard, &data);
	if(!rc){
		return false;
	}

	if(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
		throw std::exception("Is a directory?");
	}

	return true;
}

static int file_length(const platform::string_t &filename)
{
	DWORD written = 0;
	HANDLE h = CreateFile(filename.c_str(), GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h == INVALID_HANDLE_VALUE) {
		throw std::exception("Failed to create file");
	}

	LARGE_INTEGER size;
	BOOL rc = GetFileSizeEx(h, &size);
	if(!rc){
		throw std::exception("Faield to get file size");
	}

	CloseHandle(h);

	return (int) size.QuadPart;
}


static bool delete_file(const platform::string_t &filename)
{
	return DeleteFile(filename.c_str());
}



#endif
