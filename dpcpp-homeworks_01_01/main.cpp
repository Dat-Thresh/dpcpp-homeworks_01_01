#include <iostream>
#include <string>
#include <assert.h>

struct Query {

	std::string column;
	std::string from;
	std::string where;

};

class SqlSelectQueryBuilder{
	Query q;
	std::string sql_request;
	bool AddColumnCalled = false;

public:
	explicit SqlSelectQueryBuilder() {
		sql_request = "SELECT ";
	}

	SqlSelectQueryBuilder& AddColumn(const std::string& column){
		if (!AddColumnCalled) {
			q.column = column;
			AddColumnCalled = true;
		}
		else {
			q.column += ", " + column;
		}
		return *this;
	}

	SqlSelectQueryBuilder& AddFrom(std::string from) {
		q.from = from;
		return *this;
	}

	SqlSelectQueryBuilder& AddWhere(std::string a, std::string b) {
		if (q.where.empty()) {
			q.where = a + "=" + b;
		}
		else {
			q.where += " AND " + a + "=" + b;
		}
		return *this;
	}

	std::string BuildQuery() {
		if (AddColumnCalled == false) { q.column = "*"; }
		sql_request += q.column + " FROM " + q.from + " WHERE " + q.where + ";";
		//std::cout <<"We have: " <<  sql_request << std::endl;
		return sql_request;
	}

};


int main() {

	SqlSelectQueryBuilder query_builder;
	query_builder.AddColumn("name").AddColumn("phone");
	query_builder.AddFrom("students");
	query_builder.AddWhere("id", "42").AddWhere("name", "John");
	

	//std::cout <<"Tasked:  SELECT name, phone FROM students WHERE id=42 AND name=John;" << std::endl;

	query_builder.BuildQuery();
	/*static_assert(query_builder.BuildQuery(),
		"SELECT name, phone FROM students WHERE id=42 AND name=John;");*/

	return 0;
}