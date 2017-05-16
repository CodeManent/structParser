#ifndef ScriptParser_APT_Traits_H_
#define ScriptParser_APT_Traits_H_
#pragma once

#include "Visitor.h"

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

namespace ScriptParser{
	namespace APT{

		/*
		 * Node trait to represent to namage the name of a node .
		 */
		class Named{
		public:
			Named( std::string name )
				: name_( name )
			{
			}

			virtual ~Named()
			{
			}

			// Returns the name of the node
			virtual std::string getName() const
			{
				return name_;
			}

			// Sets the name of the node
			virtual void setName( std::string name )
			{
				name_ = name;
			};

		private:
			// The actual name of the node
			std::string name_;
		};


		class Type: public Named
		{
		public:
			Type( std::string name )
				: Named( name )
			{
			}

			virtual ~Type()
			{
			}

			virtual void accept( Visitor * visitor ) = 0;

		};



		/*
		 * Node trait to represent the type of a node.
		 */
		class Typed{
		public:
			/*
			Typed()
				: type_( nullptr )
			{
			}
			*/

			Typed( std::unique_ptr<Type> type )
				: type_( std::move( type ) )
			{
			}

			virtual ~Typed()
			{
			}

			// Reset the type for the current node
			virtual void setType( std::unique_ptr<Type> type)
			{
				type_ = std::move( type );
			}

			virtual Type& inspectType() const
			{
				return *type_.get();
			}

		private:
			// The type of the node
			std::unique_ptr<Type> type_;
		};





		template<class T, typename CONT = std::vector<std::unique_ptr<T>>>
		/*
		 * Node trait to signify that the current node is a container.
		 * Manages the contined elements
		 */
		class Container{
		public:
			typedef typename CONT::iterator iterator;
			typedef typename CONT::const_iterator const_iterator;
			typedef typename CONT::reverse_iterator reverse_iterator;
			typedef typename CONT::const_reverse_iterator const_reverse_iterator;


			Container()
			{
			}

			virtual ~Container()
			{
			}

			// Returns an iterator to the first element of the container
			virtual iterator begin(){
				return members_.begin();
			}

			// Returns an iterator after the last element of the container
			virtual iterator end(){
				return members_.end();
			}

			//Returns a reverse iterator at the last element of the container
			virtual reverse_iterator rbegin(){
				return members_.rbegin();
			}

			// Returns a reverse iterator befor the first element of the container
			virtual reverse_iterator rend(){
				return members_.rend();
			}

			// Returns a const iterator at the firat element of the container
			virtual const_iterator cbegin() const{
				return members_.cbegin();
			}

			// Returns a const iterator after the last element of the container
			virtual const_iterator cend() const{
				return members_.cend();
			}

			// Returns a const reverse iterator at the last element of the container
			virtual const_reverse_iterator crbegin() const{
				return members_.crbegin();
			}

			// Returns a const reverse iterator before the firat element of the iterator
			virtual const_reverse_iterator crend() const{
				return members_.crend();
			}

			// Appends the elements of the passed container to the end of the current container
			virtual void append( CONT &toAppend ){
				members_.insert(
					members_.end(),
					std::move_iterator<iterator>( toAppend.begin() ),
					std::move_iterator<iterator>( toAppend.end() )
					);

				toAppend.clear();
			}


		private:
			//T The actual container of the elements
			CONT members_;
		};
	}
}

#endif
