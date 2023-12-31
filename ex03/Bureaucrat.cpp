#include "Bureaucrat.hpp"

class Bureaucrat::GradeTooHighException : public std::exception
{
private:
    const char* error;
public:
    GradeTooHighException() : error ( "Grade Too High" ) {}

    virtual const char* what() const throw()
    {
        return ( error );
    } 
};

class Bureaucrat::GradeTooLowException : public std::exception
{
private:
    const char* error;
public:
    GradeTooLowException() : error ( "Grade Too Low" ) {}

    virtual const char* what() const throw()
    {
        return ( error );
    }
};

Bureaucrat::Bureaucrat() : name ( "Default" ), grade ( 150 ) {}

Bureaucrat::Bureaucrat( const std::string bName, int bGrade )
    : name ( bName )
{
    if ( bGrade < 1)
        throw GradeTooHighException();
    else if ( bGrade > 150 )
        throw GradeTooLowException();
    else
        grade = bGrade;
}

Bureaucrat::~Bureaucrat() {}

Bureaucrat::Bureaucrat( const Bureaucrat& obj ) : name ( obj.name ), grade ( obj.grade ) {}

Bureaucrat& Bureaucrat::operator=(  const Bureaucrat& rhs)
{
    grade = rhs.grade;
    return ( *this );
}

const std::string& Bureaucrat::getName () const
{
    return ( name );
}

const int& Bureaucrat::getGrade() const
{
    return ( grade );
}

void Bureaucrat::increment()
{
    if ( grade > 1 )
        grade -= 1;
    else
        throw GradeTooHighException();
}

void Bureaucrat::decrement()
{
    if ( grade < 150 )
        grade += 1;
    else
        throw GradeTooLowException();
}

void Bureaucrat::signedForm( bool sign, const std::string& fName ) const
{
    if ( !sign )
        std::cout << name << " couldn't sign " << fName << " because ";
    else
        std::cout << name << " signed " << fName << std::endl;
}

void Bureaucrat::executeForm( AForm const & form )
{
    try
    {
        form.execute( *this );
    }
    catch( const std::exception& e )
    {
        std::cerr << FRED( "Exception: " ) << e.what() << '\n';
    }
    
}

std::ostream& operator<<( std::ostream& out, const Bureaucrat& bureaucrat )
{
    out << bureaucrat.getName() << " bureaucrat grade " <<  bureaucrat.getGrade();
    return ( out );
}
