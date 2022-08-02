extern "C" void set_path(char *pathtodata)
{
	path = string(pathtodata);
}

extern "C" void set_keys(char *key, char *name)
{
	person[string(key)] = string(name);
}
