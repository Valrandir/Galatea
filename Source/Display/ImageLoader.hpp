namespace Galatea
{
	namespace Display
	{
		struct ImageLoader
		{
			virtual Image* LoadImage(const char* file) const = 0;
		};
	}
}
