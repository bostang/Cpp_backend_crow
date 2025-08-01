#include <iostream>
#include <string>
#include <vector>
#include <crow.h>      // Include the Crow web framework

// A simple struct to represent a user.
// This is our data model for the API.
struct User {
    int id;
    std::string name;
};

// Global vector to store our user data.
// In a real application, this would be a database.
std::vector<User> users = {
    {1, "Alice"},
    {2, "Bob"},
    {3, "Charlie"}
};

// Function to find a user by their ID
User* find_user_by_id(int id) {
    for (auto& user : users) {
        if (user.id == id) {
            return &user;
        }
    }
    return nullptr;
}

int main() {
    // Create a Crow application instance
    crow::SimpleApp app;

    // Define a route for the root URL ("/")
    // This will respond with a simple greeting.
    CROW_ROUTE(app, "/")([]() {
        return "Hello, C++ API!";
    });

    // Define a route to get all users
    // It returns a JSON array of all users.
    CROW_ROUTE(app, "/users")
        .methods("GET"_method)
    ([&]() {
        // Create a JSON array using Crow's native wvalue
        crow::json::wvalue users_json({});
        for (size_t i = 0; i < users.size(); ++i) {
            users_json[i]["id"] = users[i].id;
            users_json[i]["name"] = users[i].name;
        }
        return users_json;
    });

    // Define a route to get a single user by ID
    CROW_ROUTE(app, "/users/<int>")
        .methods("GET"_method)
    ([&](int id) {
        User* user = find_user_by_id(id);
        if (user) {
            // Create a JSON object for the user
            crow::json::wvalue user_json;
            user_json["id"] = user->id;
            user_json["name"] = user->name;
            // Return a crow::response with status OK and the JSON body
            return crow::response(crow::status::OK, user_json.dump());
        } else {
            // If the user is not found, return a 404 Not Found error with a JSON message
            crow::json::wvalue error_json;
            error_json["error"] = "User not found";
            return crow::response(crow::status::NOT_FOUND, error_json.dump());
        }
    });

    // Define a route to add a new user
    CROW_ROUTE(app, "/users")
        .methods("POST"_method)
    ([&](const crow::request& req) {
        auto x = crow::json::load(req.body);
        if (!x || !x.has("name")) {
            // Bad request if JSON is invalid or 'name' is missing
            crow::json::wvalue error_json;
            error_json["error"] = "Invalid request body. 'name' field is required.";
            return crow::response(crow::status::BAD_REQUEST, error_json.dump());
        }

        // Find the next available ID
        int new_id = 0;
        if (!users.empty()) {
            new_id = users.back().id + 1;
        } else {
            new_id = 1;
        }

        // Create a new user and add it to our vector
        User new_user = {new_id, x["name"].s()};
        users.push_back(new_user);

        // Return the newly created user with a 201 Created status
        crow::json::wvalue new_user_json;
        new_user_json["id"] = new_user.id;
        new_user_json["name"] = new_user.name;
        return crow::response(crow::status::CREATED, new_user_json.dump());
    });

    // Set the server to listen on port 8080
    app.port(8080).multithreaded().run();

    return 0;
}

