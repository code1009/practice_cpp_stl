/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// https://linkmemo.tistory.com/248





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <iostream>
#include <coroutine>
#include <concepts>
#include <exception>





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//using namespace std;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
struct cotask_noreturn
{
	struct promise_type;
	using handle_type = std::coroutine_handle<promise_type>;

	struct promise_type
	{
		std::exception_ptr exception_;

		cotask_noreturn get_return_object() 
		{
			return cotask_noreturn(handle_type::from_promise(*this));
		}

		std::suspend_always initial_suspend() 
		{
			return {};
		}

		std::suspend_always final_suspend() noexcept 
		{
			return {};
		}

		void unhandled_exception() 
		{
			exception_ = std::current_exception();
		}

		void return_void() 
		{
		}
	};

	handle_type handler_;

	cotask_noreturn(handle_type handler) : handler_(handler) {}

	~cotask_noreturn()
	{
		handler_.destroy();
	}

	bool done() 
	{
		return handler_.done();
	}

	void operator()()
	{
		handler_();
		if (handler_.promise().exception_)
			std::rethrow_exception(handler_.promise().exception_);
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cotask_noreturn cotask_func_a()
{
	std::cout << "cotask_func_a 01" << std::endl;
	co_await std::suspend_always();
	std::cout << "cotask_func_a 02" << std::endl;
}

cotask_noreturn cotask_func_b()
{
	std::cout << "cotask_func_b 01" << std::endl;
	co_await std::suspend_always();
	std::cout << "cotask_func_b 02" << std::endl;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int practice_main(int argc, char* argv[])
{
	auto cotask0 = cotask_func_a();
	auto cotask1 = cotask_func_b();


	while (!cotask0.done() || !cotask1.done())
	{
		if (!cotask0.done())
		{
			cotask0();
		}

		if (!cotask1.done())
		{
			cotask1();
		}
	}

	return 0;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// end of namespace
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int practice_cpp_stl_coroutine_0(void)
{
	return practice_main(0, nullptr);
}




