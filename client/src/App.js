import React from 'react';
import { BrowserRouter as Router, Redirect, Route, Switch } from "react-router-dom";
import './App.css';
import { DetailPage } from './page/detail';
import { ListPage } from './page/list';



class App extends React.Component {

  state = {
    list: null,
  }

  componentDidMount() {
  }

  componentWillUnmount() {

  }

  render() {


    return (
      <div className="App">

        {<Router>
          <Switch>


            <Route path="/list/:page">
              <ListPage />
            </Route>


            <Route path="/detail/:id">
              <DetailPage />
            </Route>

            <Route path="/">
              <Redirect push to="/list/0"></Redirect>
            </Route>
          </Switch>
        </Router>}

      </div>
    );
  }
}

export default App;
