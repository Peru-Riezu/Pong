/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_uint256.hpp                                                  */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/09/08 00:07:02                                            */
/*   Updated:  2024/09/09 14:41:01                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic warning "-Weverything"
#pragma GCC diagnostic ignored "-Wempty-translation-unit"
#pragma GCC diagnostic ignored "-Wunused-macros"
#pragma GCC diagnostic ignored "-Wextra-semi"
#pragma GCC diagnostic ignored "-Wunsafe-buffer-usage"
#pragma GCC diagnostic ignored "-Wc++98-compat"
#pragma GCC diagnostic ignored "-Wwritable-strings"
#pragma GCC diagnostic ignored "-Wlanguage-extension-token"
#pragma GCC diagnostic ignored "-Wpre-c++20-compat-pedantic"
#pragma GCC diagnostic ignored "-Wc++20-designator"
#pragma GCC diagnostic ignored "-Wc++98-compat-extra-semi"
;

#define UINT128_MAX (~__uint128_t(0))

class c_uint256
{
	private:
		__uint128_t val[2];

	public:
		explicit c_uint256(void) : val{0, 0}
		{
		}

		explicit c_uint256(__uint128_t exemplum) : val{exemplum, 0}
		{
		}

		~c_uint256(void)
		{
		}

		c_uint256(c_uint256 const &exemplum) : val{exemplum.val[0], exemplum.val[1]}
		{
		}

		c_uint256 const &operator=(c_uint256 const &exemplum)
		{
			if (this == &exemplum)
			{
				return (*this);
			}
			val[0] = exemplum.val[0];
			val[1] = exemplum.val[1];
			return (*this);
		}

		c_uint256 operator+(__uint128_t addend) const
		{
			c_uint256 res(*this);

			if (res.val[0] > UINT128_MAX - addend)
			{
				res.val[0] -= ((UINT128_MAX - addend) + 1);
				res.val[1]++;
				return (res);
			}
			res.val[0] += addend;
			return (res);
		}

		c_uint256 operator-(__uint128_t subtrahend) const
		{
			c_uint256 res(*this);

			if (res.val[0] < subtrahend)
			{
				res.val[0] += ((UINT128_MAX - subtrahend) + 1);
				res.val[1]--;
				return (res);
			}
			res.val[0] -= subtrahend;
			return (res);
		}

		c_uint256 operator*(__uint128_t multiplier) const
		{
			c_uint256 res(0);

			for (__uint128_t i = 0; (__uint128_t(1) << i) <= multiplier; i++)
			{
				if ((multiplier & (__uint128_t(1) << i)) != 0)
				{
					res = res + c_uint256(this->val[0] << i, this->val[0] >> (128U - i));
				}
			}
			res.val[1] += this->val[1] * multiplier;
			return (res);
		}

		c_uint256 operator/(__uint128_t divisor) const
		{
			c_uint256 res(*this);

			res.val[0] /= divisor;
			res.val[0] += res.val[1] % divisor;
			res.val[1] /= divisor;
			return (res);
		}

		__uint128_t *operator&(void)
		{
			return (&val[0]);
		}
};

#pragma GCC diagnostic pop
