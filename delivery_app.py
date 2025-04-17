pip install flask

from flask import Flask, jsonify, request

app = Flask(__name__)

# In-memory data storage
restaurants = {
    1: {"name": "Tasty Bites", "menu": {1: {"item": "Burger", "price": 5.99}, 2: {"item": "Pizza", "price": 8.99}}},
    2: {"name": "Sushi World", "menu": {1: {"item": "Salmon Roll", "price": 10.99}, 2: {"item": "Tuna Roll", "price": 11.49}}}
}

orders = []
order_id_counter = 1

# Routes
@app.route('/')
def home():
    return jsonify({"message": "Welcome to Food Delivery App!"})

@app.route('/restaurants', methods=['GET'])
def get_restaurants():
    return jsonify(restaurants)

@app.route('/restaurant/<int:rest_id>/menu', methods=['GET'])
def get_menu(rest_id):
    if rest_id in restaurants:
        return jsonify(restaurants[rest_id]["menu"])
    return jsonify({"error": "Restaurant not found"}), 404

@app.route('/order', methods=['POST'])
def place_order():
    global order_id_counter
    data = request.json
    rest_id = data.get("restaurant_id")
    items = data.get("items")  # List of item IDs

    if rest_id not in restaurants:
        return jsonify({"error": "Restaurant not found"}), 404

    total = 0
    menu = restaurants[rest_id]["menu"]
    ordered_items = []

    for item_id in items:
        if item_id in menu:
            ordered_items.append(menu[item_id])
            total += menu[item_id]["price"]
        else:
            return jsonify({"error": f"Item {item_id} not found"}), 404

    order = {
        "order_id": order_id_counter,
        "restaurant": restaurants[rest_id]["name"],
        "items": ordered_items,
        "total": round(total, 2),
        "status": "Pending"
    }

    orders.append(order)
    order_id_counter += 1

    return jsonify({"message": "Order placed", "order": order})

@app.route('/orders', methods=['GET'])
def get_orders():
    return jsonify(orders)

if __name__ == '__main__':
    app.run(debug=True)
