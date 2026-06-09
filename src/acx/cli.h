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
	inline Result<menu_option_t> get_option(std::istream& is) {
		string soption;
		menu_option_t option = -1;
		if (!std::getline(is, soption)) {
			return Ok(0);
		}
		try {
			option = static_cast<menu_option_t>(std::stoi(trim(soption)));
		}
		catch (const std::invalid_argument&) {
			return Err<menu_option_t>(ErrorCode::INVALID_ARGUMENT, string(ERR_NOT_NUMBER));
		}
		if (option < 0) {
			return Err<menu_option_t>(ErrorCode::INVALID_ARGUMENT, string(ERR_MENU_OPT_BELOW_ZERO));
		}
		return Ok(option);
	}

	inline void print_error(std::ostream& os, Error e) {
		os << MSG_ERROR_PREFIX << static_cast<u16>(e.code()) << TXT_COLON << TXT_SPACE << e.message() << NL;
	}

	inline void clear_output(std::ostream& os) {
		os << "\x1B[2J\x1B[H";
		os.flush();
	}


} // namespace acx


#endif
