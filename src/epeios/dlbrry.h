/*
	Copyright (C) 1999-2017 Claude SIMON (http://q37.info/contact/).

	This file is part of the Epeios framework.

	The Epeios framework is free software: you can redistribute it and/or
	modify it under the terms of the GNU Affero General Public License as
	published by the Free Software Foundation, either version 3 of the
	License, or (at your option) any later version.

	The Epeios framework is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	Affero General Public License for more details.

	You should have received a copy of the GNU Affero General Public License
	along with the Epeios framework.  If not, see <http://www.gnu.org/licenses/>
*/

// Dynamic LiBRaRY 

#ifndef DLBRRY__INC
# define DLBRRY__INC

# define DLBRRY_NAME		"DLBRRY"

# if defined( E_DEBUG ) && !defined( DLBRRY_NODBG )
#  define DLBRRY_DBG
# endif

# include "err.h"
# include "flw.h"
# include "tol.h"
# include "ntvstr.h"

# define DLBRRY_UNDEFINED	NULL

namespace dlbrry {
	typedef void *library_handler__;

	class dynamic_library___
	{
	private:
		library_handler__  _LibraryHandler;
		bso::bool__ _LoadLibrary( const ntvstr::string___ &Name );
		bso::bool__ _UnloadLibrary( void  );
	public:
		void reset( bso::bool__ P = true )
		{
			if ( P ) {
				if ( _LibraryHandler != DLBRRY_UNDEFINED ) {
					if ( !_UnloadLibrary() )
						qRSys();
				}
			}

			_LibraryHandler = NULL;
		}
		dynamic_library___( void )
		{
			reset( false );
		}
		~dynamic_library___( void )
		{
			reset();
		}
		bso::bool__ Init(
            const ntvstr::string___ &LibraryName,
			err::handling__ ERRHandling = err::h_Default )
		{
			reset();

			if ( _LoadLibrary( LibraryName ) )
				return true;

			if ( ERRHandling != err::hUserDefined )
				qRSys();

			return false;
		}
		bso::bool__ IsInitialized( void ) const
		{
			return _LibraryHandler != DLBRRY_UNDEFINED;
		}
		void *GetFunction( const char *FunctionName );
	};

	template <typename function> function GetFunction(
		const char *FunctionName,
		dynamic_library___ &Library )
	{
		if ( !Library.IsInitialized() )
			qRFwk();

		return (function)Library.GetFunction( FunctionName );
	}
}

#endif
