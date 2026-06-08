import { useState } from "react";
import "./App.css";

export default function App() {
  const [todo, setTodo] = useState("");
  const [todos, setTodos] = useState([]);

  const addTodo = () => {
    if (todo.trim() === "") return;
    setTodos([...todos, { text: todo, completed: false }]);
    setTodo("");
  };

  const handleKeyDown = (e) => {
    if (e.key === "Enter") addTodo();
  };

  const deleteTodo = (index) => {
    setTodos(todos.filter((_, i) => i !== index));
  };

  const markDone = (index) => {
    const updated = [...todos];
    updated[index].completed = true;
    setTodos(updated);
  };

  return (
    <div className="container">
      <h1>Todo List</h1>

      <input
        type="text"
        placeholder="Enter a task..."
        value={todo}
        onChange={(e) => setTodo(e.target.value)}
        onKeyDown={handleKeyDown}
      />

      <button onClick={addTodo}>Add</button>

      <ul>
        {todos.map((t, index) => (
          <li key={index} className={t.completed ? "done" : ""}>
            {t.text}

            <div>
              {!t.completed && (
                <button
                  className="done-btn"
                  onClick={() => markDone(index)}
                >
                  Done
                </button>
              )}

              <button
                className="delete-btn"
                onClick={() => deleteTodo(index)}
              >
                Cancel
              </button>
            </div>
          </li>
        ))}
      </ul>
    </div>
  );
}

