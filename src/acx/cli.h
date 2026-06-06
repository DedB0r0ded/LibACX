#pragma once
#ifdef ACX_CLI


#include <acx/aliases.h>
#include <acx/result.h>
#include <acx/strings.h>


namespace acx {


	struct AppState {
		std::ostream& os;
		std::istream& is;
		bool first_run = true;

		AppState(std::ostream& os, std::istream& is) : os{ os }, is{ is } {

		}
	};

	inline void await_return(std::istream& is) {
		string dummy;
		getline(is, dummy);
	}

	// Utility function prototype
	inline Result<int> get_option(std::istream& is) {
		string soption;
		int option = -1;
		if (!std::getline(is, soption)) {
			return Ok(0);
		}
		try {
			option = std::stoi(trim(soption));
		}
		catch (const std::invalid_argument&) {
			return Err<int>(ErrorCode::INVALID_ARGUMENT, string(ERR_NOT_NUMBER));
		}
		if (option < 0) {
			return Err<int>(ErrorCode::INVALID_ARGUMENT, string(ERR_MENU_OPT_BELOW_ZERO));
		}
		return Ok(option);
	}


} // namespace acx


#endif
