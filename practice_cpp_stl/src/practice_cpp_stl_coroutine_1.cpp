/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// https://en.cppreference.com/w/cpp/language/coroutines#co_await
// 
//===========================================================================
// 
// Windows Fiber랑 promise이 유사한 것?
//
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <iostream>
#include <coroutine>
#include <concepts>
#include <exception>





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
struct promise;

struct coroutine : std::coroutine_handle<promise>
{
	using promise_type = ::promise;
};

struct promise
{
	coroutine get_return_object() 
	{
		return { coroutine::from_promise(*this) };
	}

	std::suspend_always initial_suspend() noexcept 
	{
		return {};
	}

	std::suspend_always final_suspend() noexcept 
	{
		return {};
	}

	void return_void() {}
	
	void unhandled_exception() {}
};

struct S
{
	int i;

	coroutine f()
	{
		std::cout << "코루틴함수-a="  << i++ << std::endl;
		co_await std::suspend_always();

		std::cout << "코루틴함수-b=" << i++ << std::endl;
		co_await std::suspend_always();

		std::cout << "코루틴함수-c=" << i++ << std::endl;
		co_await std::suspend_always();

		co_return;
	}
};

S get_coroutine(int x)
{
	S instance{ x };

	return instance;
}






/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int practice_main(int argc, char* argv[])
{
	auto instance = get_coroutine(3);
	auto i = instance.f();


	while(1)
	{
		std::cout << "메인함수 루프-a" << std::endl;

		if (!i.done())
		{
			i();
		}
		else
		{
			break;
		}
	}

	//i(); // 예외 발생(0x0000000000000000, practice_cpp_stl.exe): 0xC0000005: 0x0000000000000000 위치를 실행하는 동안 액세스 위반이 발생했습니다..

	i.destroy(); // 호출 안하면 메모리릭 발생


	return 0;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// end of namespace
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int practice_cpp_stl_coroutine_1(void)
{
	return practice_main(0, nullptr);
}




