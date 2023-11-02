#include <iostream>

using namespace std;

class Book
{
private:
    char* title;
    char* authors;
    int publishingYear;
    friend class Printer;
public:
    Book()
    {
        publishingYear = 0;
        title = authors = nullptr;
    }

    Book(const char* title, const char* authors, int publishingYear)
    {
        this->title = new char[strlen(title) + 1];
        for (size_t i = 0; i < strlen(title); i++) {
            this->title[i] = title[i];
        }
        this->title[strlen(title)] = '\0';
        this->authors = new char[strlen(authors) + 1];
        for (size_t i = 0; i < strlen(authors); i++) {
            this->authors[i] = authors[i];
        }
        this->authors[strlen(authors)] = '\0';
        this->publishingYear = publishingYear;
    }


    Book(const Book& book)
    {
        this->title = new char[strlen(book.title) + 1];
        for (size_t i = 0; i < strlen(book.title); i++) {
            this->title[i] = book.title[i];
        }
        this->title[strlen(book.title)] = '\0';
        this->authors = new char[strlen(book.authors) + 1];
        for (size_t i = 0; i < strlen(book.authors); i++) {
            this->authors[i] = book.authors[i];
        }
        this->authors[strlen(book.authors)] = '\0';
        this->publishingYear = book.publishingYear;
    }

    void setTitle(const char* title)
    {
        this->title = new char[strlen(title) + 1];
        for (size_t i = 0; i < strlen(title); i++) {
            this->title[i] = title[i];
        }
        this->title[strlen(title)] = '\0';
    }

    void setAuthors(const char* authors)
    {
        this->authors = new char[strlen(authors) + 1];
        for (size_t i = 0; i < strlen(authors); i++) {
            this->authors[i] = authors[i];
        }
        this->authors[strlen(authors)] = '\0';
    }

    void setPublishingYear(int publishingYear)
    {
        this->publishingYear = publishingYear;
    }

    char* getTitle() const
    {
        return title;
    }

    char* getAuthors() const
    {
        return authors;
    }

    int getPublishingYear() const
    {
        return publishingYear;
    }

    ~Book()
    {
        delete[] title;
        delete[] authors;
    }

    friend bool checkAuthor(Book book, const char* author)
    {
        char* authorsCopy = new char[strlen(book.authors) + 1];
        strcpy(authorsCopy, book.authors);

        char* token = strtok(authorsCopy, ",");
        while (token != NULL)
        {
            while (isspace(*token)) token++;
            char* end = token + strlen(token) - 1;
            while (end > token && isspace(*end)) end--;
            *(end + 1) = 0;

            if (strcmp(token, author) == 0)
            {
                delete[] authorsCopy;
                return true;
            }
            token = strtok(NULL, ",");
        }

        delete[] authorsCopy;
        return false;
    }

    void printBook() {
        printf("%s\n%s\n%d", this->title, this->authors, this->publishingYear);
    }
};

class Printer
{
public:
    static void printBook(const Book book)
    {
        cout << book.title << endl;

        char* author = strtok(book.authors, ",");
        while (author != nullptr) {
            if (author[0] == ' ') author++;
            cout << author << endl;
            author = strtok(nullptr, ",");
        }

        cout << book.publishingYear;

    }
};

int main()
{
}
