#ifndef CATEGORY_HPP
#define CATEGORY_HPP


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		SceneAirLayer		= 1 << 0
	};
}

#endif // CATEGORY_HPP
