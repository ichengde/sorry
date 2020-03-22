import React, { useState, useEffect } from 'react';
import './App.css';

import {
  BrowserRouter as Router,
  Switch,
  Route,
  Link,
  useParams,
  Redirect
} from "react-router-dom";

import { ListPage } from './page/list'
import { DetailPage } from './page/detail'

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
