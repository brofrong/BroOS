int bmpDrow(int addr)
{
	int bfOffBits = *(addr +0x0a);
	int width = *(addr+0x12);
	int height = *(addr+0x14);
	int BitCount = *(addr+0x18);
	return 0;
}
