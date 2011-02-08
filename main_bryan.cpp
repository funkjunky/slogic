int main() { }


#if 0
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/function.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <utility>
#include <sstream>

#include "subj_logic.hpp"

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace fusion = boost::fusion;

using ascii::space_type;

typedef std::list<std::string> list_type;
typedef list_type arg_list;
typedef boost::function<std::string (arg_list)> func_type;
typedef std::pair<int, func_type> func_desc;
typedef boost::shared_ptr<Subj_logic::Atom> atom_ptr;

std::map<std::string, func_desc> function_table;
std::map<std::string, atom_ptr> atom_table;
std::map<std::string, Subj_logic::Sub_frame> frame_table;
std::map<std::string, Subj_logic::Opinion> opinion_table;

std::string create_atom(arg_list args)
{
    std::string name = args.front();
    atom_ptr atom(new Subj_logic::Atom());
    if (atom_table.insert(std::make_pair(name, atom)).second)
	std::cout << "Created atom with label: " << name << std::endl;
    else
	std::cout << "Duplicate atom: " << name << std::endl;
    return "nil";
}

std::string create_frame(arg_list args)
{
    std::string name = args.front();
    args.pop_front();

    std::set<Subj_logic::Atom*> temp;
    for (arg_list::iterator i = args.begin(); i != args.end(); ++i)
    {
	if (atom_table.find(*i) == atom_table.end())
	{
	    std::cout << "Error. No such atom: " << *i << std::endl;
	    return "nil";
	}
	Subj_logic::Atom* a = atom_table[*i].get();
	temp.insert(a);
    }

    Subj_logic::Sub_frame f(temp.begin(), temp.end());
    if (frame_table.insert(std::make_pair(name, f)).second)
	std::cout << "Created frame with label: " << name << std::endl;
    else
	std::cout << "Duplicate frame: " << name << std::endl;
    return "nil";
}

std::string create_opinion(arg_list args)
{
    std::string name = args.front();
    args.pop_front();

    Subj_logic::Opinion op;
    
    if (!args.empty())
    {
	std::string frame = args.front();
	if (frame_table.find(frame) == frame_table.end())
	{
	    std::cout << "Error. No such frame " << frame << std::endl;
	    return "nil";
	}
	Subj_logic::Sub_frame f = frame_table[frame];
	op.set_frame(f);
    }

    if (opinion_table.insert(std::make_pair(name, op)).second)
	std::cout << "Created opinion with label: " << name << std::endl;
    else
	std::cout << "Duplicate opinion: " << name << std::endl;
    return "nil";
}


struct eval_list_impl
{
    template <typename Arg>
    struct result
    {
	typedef std::string type;
    };

    template <typename Arg>
    std::string operator()(Arg list) const
    {
	if (list.size() == 0)
	{
	    return "nil";
	}
	else
	{
	    // Check to see if it's a function.
	    if (function_table.find(list.front()) == function_table.end())
	    {
		std::string output = "(";
		for (list_type::iterator i = list.begin(); 
		     i != list.end(); ++i)
		    output += (*i + " ");
		output += ")";
		return output;
	    }
	    else
	    {
		std::string fname = list.front();
		func_type f = function_table[fname].second;
		int airity = function_table[fname].first;

		list.pop_front();
		if ((int)list.size() != airity && airity != -1)
		{
		    std::cout << "Wrong number of arguments to function " << fname << std::endl;
		    return "nil";
		}

		return f(list);
	    }
	}
    }
};

boost::phoenix::function<eval_list_impl> eval_list;

void print_element(const std::string& elem)
{
    std::cout << elem << std::endl;
}

template <typename Func>
void insert_function(std::string tag, int airity, Func f)
{
    function_table.insert(std::make_pair(tag, std::make_pair(airity, f)));
}

template <typename Iter>
struct main_grammar : qi::grammar<Iter, fusion::unused_type, space_type>
{
    main_grammar() : main_grammar::base_type(start)
    {
	using qi::lexeme;
	using qi::char_;
	using qi::int_;
	using qi::_val;
	using qi::_1;
	using qi::lexeme;

	integer %= lexeme[+char_("0-9")];
	fraction %= integer >> char_('/') >> integer;
	number = fraction[_val = _1] | integer[_val = _1];
	
	token %= lexeme[+char_("a-zA-Z!@#$%^&*-_=+")];

	element = number[_val = _1] | token[_val = _1]
	    | list[_val = eval_list(_1)]
	    ;
	
	list %= '(' >> *element >> ')';

	start = element[&print_element];
    }

    qi::rule<Iter, std::string(), space_type> integer;
    qi::rule<Iter, std::string(), space_type> fraction;
    qi::rule<Iter, std::string(), space_type> number;

    qi::rule<Iter, std::string(), space_type> token;

    qi::rule<Iter, std::string(), space_type> element;
    qi::rule<Iter, list_type(), space_type> list;

    qi::rule<Iter, fusion::unused_type, space_type> start;
};

int main()
{
    // Create the function table.
    insert_function("create-atom", 1, &create_atom);
    insert_function("create-frame", -1, &create_frame);
    insert_function("create-opinion", 2, &create-opinion);

    std::string input;
    std::cout << "> ";
    while (std::getline(std::cin, input))
    {
	typedef std::string::const_iterator Iter;
	main_grammar<Iter> g;

	Iter iter = input.begin(), end = input.end();
	bool r = qi::phrase_parse(iter, end, g, ascii::space);

	if (r && iter == end)
	    std::cout << "> ";
	else
	    std::cout << "bad" << std::endl
		      << "> ";
    }
}
#endif
